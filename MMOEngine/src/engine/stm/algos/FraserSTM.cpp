/*
 * FraserSTM.cpp
 *
 *  Created on: 11/11/2011
 *      Author: victor
 */

#include "engine/stm/Transaction.h"
#include "engine/stm/TransactionalMemoryManager.h"
#include "FraserSTM.h"

using namespace engine::stm;

//Warning! This is called by several threads concurrently!
bool FraserSTM::doCommit(Transaction* transaction) {
	int desiredStatus = Transaction::ABORTED;

	if (transaction->status == Transaction::UNDECIDED && transaction->readWriteObjects.size() > 0) {
		WMB();

		uint64 lastHeaderID = 0;

		for (int i = 0; i < transaction->readWriteObjects.size(); ++i) {
			Reference<TransactionalObjectHandleBase* > handle = transaction->readWriteObjects.get(i);

			uint64 hID = handle->getHeaderAddress();

			//transaction->info("hID:" + String::valueOf(hID), true);

			if (hID < lastHeaderID) {
				assert("hui" && 0);
			} else
				lastHeaderID = hID;

			Reference<Transaction*> competingTransaction = NULL;

			while (true) {
				competingTransaction = handle->acquireHeader(transaction);

				if (competingTransaction == transaction || competingTransaction == NULL) { // we acquired the transaction
					break;
				} else {
					if (competingTransaction != NULL) {
						if (competingTransaction->isCommited()) {
							TransactionalMemoryManager::instance()->increaseFailedByCompetingCommited();

							return tryFinishCommit(desiredStatus, transaction); // we failed
						} else
							competingTransaction->doCommit();
					}
				}

				Thread::yield();
			}

			if (handle->hasObjectChanged()) {
				//we fail because a previous/faster transaction commited before we did
				TransactionalMemoryManager::instance()->increaseFailedByObjectChanged();

				return tryFinishCommit(desiredStatus, transaction); // we failed
			}
		}
	}

	if (validateReadOnlyObjects(transaction))
		desiredStatus = Transaction::COMMITTED;

	return tryFinishCommit(desiredStatus, transaction);
}

bool FraserSTM::tryFinishCommit(int desiredStatus, Transaction* transaction) {
	int oldStatus = transaction->status;
	int newStatus;

	//we push final status
	while (oldStatus <= Transaction::READ_CHECKING) {
		newStatus = transaction->status.compareAndSetReturnOld(oldStatus, desiredStatus);

		if (oldStatus == newStatus)
			break;

		oldStatus = newStatus;

		Thread::yield();
	}

	WMB();

	int finalStatus = transaction->status;

	//CLEANUP
	if (finalStatus == Transaction::COMMITTED) {
		transaction->releaseReadWriteObjects();
	} else {
		transaction->discardReadWriteObjects();
	}

	transaction->cleanReadOnlyHandles();

	return finalStatus == Transaction::COMMITTED;
}

bool FraserSTM::validateReadOnlyObjects(Transaction* transaction) {
	if (transaction->status <= Transaction::READ_CHECKING && transaction->readOnlyObjects.size() > 0) {
		transaction->setState(Transaction::UNDECIDED, Transaction::READ_CHECKING);

		WMB();

		//while ((i = currentReadObjectAcquiring.increment()) < readOnlyObjects.size()) {
		for (int i = 0; i < transaction->readOnlyObjects.size(); ++i) {
			Reference<TransactionalObjectHandleBase* > handle = transaction->readOnlyObjects.get(i);

			if (handle->hasObjectChanged()) {
				TransactionalMemoryManager::instance()->increaseFailedByObjectChanged();
				return false;
			}

			Reference<Transaction*> competingTransaction = handle->getCompetingTransaction();

			if (competingTransaction != NULL) {
				while (competingTransaction->isReadChecking()) {
					if (transaction->tid < competingTransaction->tid) { // we fail the other one
						competingTransaction->setState(Transaction::READ_CHECKING, Transaction::ABORTED);
					} else { // we help
						competingTransaction->doCommit();
					}
				}

				if (competingTransaction->isCommited()) {
					if (!handle->isCopyEqualToObject()) { // this transaction will commit or already commited a new version we fail
						TransactionalMemoryManager::instance()->increaseFailedByCompetingCommited();

						return false;
					}
				}

				if (handle->hasObjectChanged()) {
					TransactionalMemoryManager::instance()->increaseFailedByObjectChanged();
					return false;
				}
			}
		}
	}

	return true;
}
