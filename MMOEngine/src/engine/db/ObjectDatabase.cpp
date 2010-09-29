#include "ObjectDatabase.h"

#include "ObjectDatabaseManager.h"

using namespace engine::db;
using namespace engine::db::berkley;

ObjectDatabase::ObjectDatabase(ObjectDatabaseManager* dbEnv, const String& dbFileName) {
	environment = dbEnv->getBerkeleyEnvironment();

	setLoggingName("ObjectDatabase " + dbFileName);
	setGlobalLogging(true);
	setLogging(false);

	databaseFileName = dbFileName;

	openDatabase();

	//setFileLogger("log/berkeley.log");
}

ObjectDatabase::~ObjectDatabase() {
	closeDatabase();

	delete objectsDatabase;
	objectsDatabase = NULL;
}

void ObjectDatabase::openDatabase() {
	DatabaseConfig config;
	config.setThreaded(true);
	//config.setTransactional(true);
	config.setAllowCreate(true);
	config.setType(DatabaseType::HASH);
	config.setReadUncommited(true);

	try {

		Transaction* transaction = environment->beginTransaction(NULL);

		objectsDatabase = environment->openDatabase(transaction, databaseFileName, "", config);

		int ret = 0;

		if ((ret = transaction->commit()) != 0) {
			error(String::valueOf(db_strerror(ret)));
		}


	} catch (Exception& e) {
		error(e.getMessage());
		exit(1);
	}
}

void ObjectDatabase::closeDatabase() {
	try {

		objectsDatabase->close(true);

		info("database closed", true);

	} catch (Exception &e) {
		error("Error closing database (" + databaseFileName + "):");
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught while trying to open berkeley DB ");
	}
}

int ObjectDatabase::getData(uint64 objKey, ObjectInputStream* objectData) {
	//Locker locker(&writeLock);

	int ret = 0;

	DatabaseEntry key, data;

	key.setData(&objKey, sizeof(uint64));

	int i = 0;

	ObjectDatabaseManager* databaseManager = ObjectDatabaseManager::instance();

	Transaction* transaction = NULL;

	do {
		ret  = -1;
		transaction = databaseManager->getBerkeleyEnvironment()->beginTransaction(NULL);

		ret = objectsDatabase->get(transaction, &key, &data, LockMode::READ_UNCOMMITED);

		if (ret == DB_LOCK_DEADLOCK) {
			info("deadlock detected in ObjectDatabse::get.. retrying iteration " + String::valueOf(i), true);
			transaction->abort();
			transaction = NULL;
		}

		++i;
	} while (ret == DB_LOCK_DEADLOCK && i < DEADLOCK_MAX_RETRIES);

	if (ret == 0) {
		objectData->writeStream((const char*) data.getData(), data.getSize());

		objectData->reset();
	} else if (ret != DB_NOTFOUND) {
		error("error in ObjectDatabase::getData ret " + String::valueOf(db_strerror(ret)));

		if (transaction != NULL)
			transaction->abort();

		throw DatabaseException("error in ObjectDatabase::getData ret " + String(db_strerror(ret)));
	}

	if (transaction != NULL) {
		transaction->commit();
	}


	return ret;
}

int ObjectDatabase::tryPutData(uint64 objKey, Stream* stream, engine::db::berkley::Transaction* transaction) {
	//Locker locker(&writeLock);
	int ret = -1;

	/*ObjectDatabaseManager* databaseManager = ObjectDatabaseManager::instance();

	CurrentTransaction* transaction = databaseManager->getCurrentTransaction();

	Transaction* transaction = databaseManager->getLocalTransaction();*/

	DatabaseEntry key, data;
	key.setData(&objKey, sizeof(uint64));
	data.setData(stream->getBuffer(), stream->size());

	ret = objectsDatabase->put(transaction, &key, &data);

	return ret;
}

int ObjectDatabase::tryDeleteData(uint64 objKey, engine::db::berkley::Transaction* transaction) {
	//Locker locker(&writeLock);
	int ret = -1;

	/*ObjectDatabaseManager* databaseManager = ObjectDatabaseManager::instance();

	CurrentTransaction* transaction = databaseManager->getCurrentTransaction();

	Transaction* transaction = databaseManager->getLocalTransaction();*/

	DatabaseEntry key;
	key.setData(&objKey, sizeof(uint64));

	ret = objectsDatabase->del(transaction, &key);

	/*StringBuffer msg;
	msg << "deleted from DB objid" << hex << objKey;
	info(msg.toString(), true);*/

	return ret;
}

int ObjectDatabase::putData(uint64 objKey, ObjectOutputStream* objectData, Object* obj) {
	ObjectDatabaseManager* databaseManager = ObjectDatabaseManager::instance();

	CurrentTransaction* transaction = databaseManager->getCurrentTransaction();

	transaction->addUpdateObject(objKey, objectData->clone(0), this, obj);

	return 0;
}

int ObjectDatabase::deleteData(uint64 objKey) {
	ObjectDatabaseManager* databaseManager = ObjectDatabaseManager::instance();

	CurrentTransaction* transaction = databaseManager->getCurrentTransaction();

	transaction->addDeleteObject(objKey, this);

	/*StringBuffer msg;
	msg << "added to deleteData objid" << hex << objKey;
	info(msg.toString(), true);*/

	return 0;
}

int ObjectDatabase::sync() {
	objectsDatabase->sync();

	return 0;
}

ObjectDatabaseIterator::ObjectDatabaseIterator(ObjectDatabase* database, bool useCurrentThreadTransaction) : Logger("ObjectDatabaseIterator") {
	databaseHandle = database->getDatabaseHandle();

	Transaction* txn = NULL;//ObjectDatabaseManager::instance()->getLocalTransaction();

/*	if (useCurrentThreadTransaction)
		txn = ObjectDatabaseManager::instance()->getLocalTransaction();*/

	cursor = databaseHandle->openCursor(txn);

	data.setReuseBuffer(true);
	key.setReuseBuffer(true);
}

ObjectDatabaseIterator::ObjectDatabaseIterator(BerkeleyDatabase* dbHandle) : Logger("ObjectDatabaseIterator") {
	databaseHandle = dbHandle;
	Transaction* txn = NULL; // ObjectDatabaseManager::instance()->getLocalTransaction();
	cursor = databaseHandle->openCursor(txn);

	data.setReuseBuffer(true);
	key.setReuseBuffer(true);
}

ObjectDatabaseIterator::~ObjectDatabaseIterator() {
	closeCursor();
}

void ObjectDatabaseIterator::resetIterator() {
	if (cursor != NULL) {
		cursor->close();
		delete cursor;
	}


	Transaction* txn = NULL;//
	//Transaction* txn = ObjectDatabaseManager::instance()->getLocalTransaction();

	cursor = databaseHandle->openCursor(txn);
}

bool ObjectDatabaseIterator::getNextKeyAndValue(uint64& key, ObjectInputStream* data) {
	try {
		if (cursor->getNext(&this->key, &this->data, LockMode::READ_UNCOMMITED) != 0)
			return false;

		key = *(uint64*) (this->key.getData());
		data->writeStream((char*)this->data.getData(), this->data.getSize());

		data->reset();

	} catch (...) {
		error("unreported exception caught in ObjectDatabaseIterator::getNextKeyAndValue(uint64& key, String& data)");
	}

	return true;
}

bool ObjectDatabaseIterator::getNextValue(ObjectInputStream* data) {
	try {
		if (cursor->getNext(&this->key, &this->data, LockMode::READ_UNCOMMITED) != 0)
			return false;

		data->writeStream((char*)this->data.getData(), this->data.getSize());

		data->reset();

	} catch(Exception &e) {
		error("Error in ObjectDatabaseIterator::getNextValue(String& data)");
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in ObjectDatabaseIterator::getNextValue(String& data)");
	}

	return true;
}

bool ObjectDatabaseIterator::getNextKey(uint64& key) {
	try {
		if (cursor->getNext(&this->key, &this->data, LockMode::READ_UNCOMMITED) != 0)
			return false;

		key =  *(uint64*)(this->key.getData());

	}  catch(Exception &e) {
		error("Error in ObjectDatabaseIterator::getNextKey");
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught  in ObjectDatabaseIterator::getNextKey(uint64& key) ");
	}

	return true;
}
