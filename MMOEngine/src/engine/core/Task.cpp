#include "Core.h"

#include "engine/db/ObjectDatabaseManager.h"

#include "engine/stm/TransactionalMemoryManager.h"

#include "TaskScheduler.h"

#include "Task.h"

#include "TaskManager.h"

Task::Task() : PriorityQueueEntry() {
	taskManager = Core::getTaskManager();

	priority = 3;
	period = 0;
}

Task::Task(uint64 mtime) : PriorityQueueEntry() {
	taskManager = Core::getTaskManager();

	nextExecutionTime.addMiliTime(mtime);

	priority = 3;
	period = 0;
}

Task::Task(Time& time) : PriorityQueueEntry() {
	taskManager = Core::getTaskManager();

	nextExecutionTime = time;

	priority = 3;
	period = 0;
}

Task::~Task() {
	if (isQueued()) {
		System::out << "ERROR: scheduled task deleted\n";
		raise(SIGSEGV);
	}
}

void Task::execute() {
#ifdef WITH_STM
	Reference<engine::stm::Transaction*> transaction = engine::stm::Transaction::currentTransaction();
	//engine::stm::Transaction* transaction = engine::stm::Transaction::currentTransaction();

	try {
		if (!transaction->start(this))
			return;

		transaction->commit();
	} catch (Exception& e) {
		Logger::console.error("exception caught while running a task");
		e.printStackTrace();
	} catch (...) {
		Logger::console.error("unreported exception caught while running a task");
	}
#else
	ObjectDatabaseManager::instance()->startLocalTransaction();

	try {
		run();

		if (isPeriodic())
			schedule(period);

	} catch (Exception& e) {
		Logger::console.error("exception caught while running a task");
		e.printStackTrace();
	} catch (...) {
		Logger::console.error("unreported exception caught while running a task");
	}

	ObjectDatabaseManager::instance()->commitLocalTransaction();
#endif
}


bool Task::isScheduled() {
	return taskManager->isTaskScheduled(this);
}

bool Task::cancel() {
	return taskManager->cancelTask(this);
}

void Task::schedule(uint64 delay) {
	taskManager->scheduleTask(this, delay);
}

void Task::schedule(Time& time) {
	taskManager->scheduleTask(this, time);
}

void Task::schedulePeriodic(uint64 delay, uint64 period) {
	setPeriod(period);

	taskManager->scheduleTask(this, delay);
}

void Task::schedulePeriodic(Time& time, uint64 period) {
	setPeriod(period);

	taskManager->scheduleTask(this, time);
}

void Task::reschedule(uint64 delay) {
	taskManager->rescheduleTask(this, delay);
}

void Task::reschedule(Time& time) {
	taskManager->rescheduleTask(this, time);
}

