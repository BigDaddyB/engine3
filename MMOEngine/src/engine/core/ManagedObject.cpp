/*
 *	engine/core/ManagedObject.cpp generated by engine3 IDL compiler 0.60
 */

#include "ManagedObject.h"

#include "engine/core/ObjectUpdateToDatabaseTask.h"

/*
 *	ManagedObjectStub
 */

ManagedObject::ManagedObject() {
	ManagedObjectImplementation* _implementation = new ManagedObjectImplementation();
	_impl = _implementation;
	_impl->_setStub(this);
}

ManagedObject::ManagedObject(DummyConstructorParameter* param) {
}

ManagedObject::~ManagedObject() {
}


void ManagedObject::_updateForWrite() {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 6);

		method.executeWithVoidReturn();
	} else
		_implementation->updateForWrite();
}

void ManagedObject::_lock(bool doLock) {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 7);
		method.addBooleanParameter(doLock);

		method.executeWithVoidReturn();
	} else
		_implementation->lock(doLock);
}

void ManagedObject::_lock(ManagedObject* obj) {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 8);
		method.addObjectParameter(obj);

		method.executeWithVoidReturn();
	} else
		_implementation->lock(obj);
}

void ManagedObject::_rlock(bool doLock) {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 9);
		method.addBooleanParameter(doLock);

		method.executeWithVoidReturn();
	} else
		_implementation->rlock(doLock);
}

void ManagedObject::_wlock(bool doLock) {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 10);
		method.addBooleanParameter(doLock);

		method.executeWithVoidReturn();
	} else
		_implementation->wlock(doLock);
}

void ManagedObject::_wlock(ManagedObject* obj) {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 11);
		method.addObjectParameter(obj);

		method.executeWithVoidReturn();
	} else
		_implementation->wlock(obj);
}

void ManagedObject::_unlock(bool doLock) {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 12);
		method.addBooleanParameter(doLock);

		method.executeWithVoidReturn();
	} else
		_implementation->unlock(doLock);
}

void ManagedObject::_runlock(bool doLock) {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 13);
		method.addBooleanParameter(doLock);

		method.executeWithVoidReturn();
	} else
		_implementation->runlock(doLock);
}

void ManagedObject::_setLockName(const String& name) {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 14);
		method.addAsciiParameter(name);

		method.executeWithVoidReturn();
	} else
		_implementation->setLockName(name);
}

bool ManagedObject::_notifyDestroy() {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 15);

		return method.executeWithBooleanReturn();
	} else
		return _implementation->notifyDestroy();
}

void ManagedObject::writeObject(ObjectOutputStream* stream) {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		_implementation->writeObject(stream);
}

void ManagedObject::readObject(ObjectInputStream* stream) {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		_implementation->readObject(stream);
}

void ManagedObject::initializeTransientMembers() {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 16);

		method.executeWithVoidReturn();
	} else
		_implementation->initializeTransientMembers();
}

void ManagedObject::updateToDatabase() {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 17);

		method.executeWithVoidReturn();
	} else
		_implementation->updateToDatabase();
}

void ManagedObject::queueUpdateToDatabaseTask() {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 18);

		method.executeWithVoidReturn();
	} else
		_implementation->queueUpdateToDatabaseTask();
}

void ManagedObject::clearUpdateToDatabaseTask() {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 19);

		method.executeWithVoidReturn();
	} else
		_implementation->clearUpdateToDatabaseTask();
}

unsigned int ManagedObject::getLastCRCSave() {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 20);

		return method.executeWithUnsignedIntReturn();
	} else
		return _implementation->getLastCRCSave();
}

void ManagedObject::setLastCRCSave(unsigned int crc) {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 21);
		method.addUnsignedIntParameter(crc);

		method.executeWithVoidReturn();
	} else
		_implementation->setLastCRCSave(crc);
}

bool ManagedObject::isPersistent() {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		return _implementation->isPersistent();
}

int ManagedObject::getPersistenceLevel() {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		return _implementation->getPersistenceLevel();
}

void ManagedObject::setPersistent(int level) {
	ManagedObjectImplementation* _implementation = (ManagedObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		_implementation->setPersistent(level);
}

DistributedObjectServant* ManagedObject::_getImplementation() {

	_updated = true;
	return _impl;
}

void ManagedObject::_setImplementation(DistributedObjectServant* servant) {
	_impl = servant;}

/*
 *	ManagedObjectImplementation
 */

ManagedObjectImplementation::ManagedObjectImplementation(DummyConstructorParameter* param) {
	_initializeImplementation();
}

ManagedObjectImplementation::~ManagedObjectImplementation() {
}


void ManagedObjectImplementation::finalize() {
}

void ManagedObjectImplementation::_initializeImplementation() {
	_setClassHelper(ManagedObjectHelper::instance());

	_serializationHelperMethod();
	_serializationHelperMethod();
}

void ManagedObjectImplementation::_setStub(DistributedObjectStub* stub) {
	_this = (ManagedObject*) stub;
}

DistributedObjectStub* ManagedObjectImplementation::_getStub() {
	return _this;
}

ManagedObjectImplementation::operator const ManagedObject*() {
	return _this;
}

void ManagedObjectImplementation::_serializationHelperMethod() {
	_setClassName("ManagedObject");

}

void ManagedObjectImplementation::readObject(ObjectInputStream* stream) {
	uint16 _varCount = stream->readShort();
	for (int i = 0; i < _varCount; ++i) {
		String _name;
		_name.parseFromBinaryStream(stream);

		uint16 _varSize = stream->readShort();

		int _currentOffset = stream->getOffset();

		if(ManagedObjectImplementation::readObjectMember(stream, _name)) {
		}

		stream->setOffset(_currentOffset + _varSize);
	}

	initializeTransientMembers();
}

bool ManagedObjectImplementation::readObjectMember(ObjectInputStream* stream, const String& _name) {
	if (_name == "_className") {
		TypeInfo<String>::parseFromBinaryStream(&_className, stream);
		return true;
	}

	if (_name == "persistenceLevel") {
		TypeInfo<int >::parseFromBinaryStream(&persistenceLevel, stream);
		return true;
	}


	return false;
}

void ManagedObjectImplementation::writeObject(ObjectOutputStream* stream) {
	int _currentOffset = stream->getOffset();
	stream->writeShort(0);
	int _varCount = ManagedObjectImplementation::writeObjectMembers(stream);
	stream->writeShort(_currentOffset, _varCount);
}

int ManagedObjectImplementation::writeObjectMembers(ObjectOutputStream* stream) {
	String _name;
	int _offset;
	uint16 _totalSize;
	_name = "persistenceLevel";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<int >::toBinaryStream(&persistenceLevel, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);


	_name = "_className";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<String>::toBinaryStream(&_className, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);
	return 2;
}

ManagedObjectImplementation::ManagedObjectImplementation() {
	_initializeImplementation();
	// engine/core/ManagedObject.idl(27):  		persistenceLevel = 0;
	persistenceLevel = 0;
	// engine/core/ManagedObject.idl(29):  		lastCRCSave = 0;
	lastCRCSave = 0;
	// engine/core/ManagedObject.idl(31):  		updateToDatabaseTask = null;
	updateToDatabaseTask = NULL;
}

void ManagedObjectImplementation::clearUpdateToDatabaseTask() {
	// engine/core/ManagedObject.idl(96):  		updateToDatabaseTask = null;
	updateToDatabaseTask = NULL;
}

unsigned int ManagedObjectImplementation::getLastCRCSave() {
	// engine/core/ManagedObject.idl(100):  		return lastCRCSave;
	return lastCRCSave;
}

void ManagedObjectImplementation::setLastCRCSave(unsigned int crc) {
	// engine/core/ManagedObject.idl(104):  		lastCRCSave = crc;
	lastCRCSave = crc;
}

bool ManagedObjectImplementation::isPersistent() {
	// engine/core/ManagedObject.idl(109):  		return persistenceLevel != 0;
	return persistenceLevel != 0;
}

int ManagedObjectImplementation::getPersistenceLevel() {
	// engine/core/ManagedObject.idl(114):  		return persistenceLevel;
	return persistenceLevel;
}

/*
 *	ManagedObjectAdapter
 */

ManagedObjectAdapter::ManagedObjectAdapter(ManagedObjectImplementation* obj) : DistributedObjectAdapter((DistributedObjectServant*) obj) {
}

Packet* ManagedObjectAdapter::invokeMethod(uint32 methid, DistributedMethod* inv) {
	Packet* resp = new MethodReturnMessage(0);

	switch (methid) {
	case 6:
		updateForWrite();
		break;
	case 7:
		lock(inv->getBooleanParameter());
		break;
	case 8:
		lock((ManagedObject*) inv->getObjectParameter());
		break;
	case 9:
		rlock(inv->getBooleanParameter());
		break;
	case 10:
		wlock(inv->getBooleanParameter());
		break;
	case 11:
		wlock((ManagedObject*) inv->getObjectParameter());
		break;
	case 12:
		unlock(inv->getBooleanParameter());
		break;
	case 13:
		runlock(inv->getBooleanParameter());
		break;
	case 14:
		setLockName(inv->getAsciiParameter(_param0_setLockName__String_));
		break;
	case 15:
		resp->insertBoolean(notifyDestroy());
		break;
	case 16:
		initializeTransientMembers();
		break;
	case 17:
		updateToDatabase();
		break;
	case 18:
		queueUpdateToDatabaseTask();
		break;
	case 19:
		clearUpdateToDatabaseTask();
		break;
	case 20:
		resp->insertInt(getLastCRCSave());
		break;
	case 21:
		setLastCRCSave(inv->getUnsignedIntParameter());
		break;
	default:
		return NULL;
	}

	return resp;
}

void ManagedObjectAdapter::updateForWrite() {
	((ManagedObjectImplementation*) impl)->updateForWrite();
}

void ManagedObjectAdapter::lock(bool doLock) {
	((ManagedObjectImplementation*) impl)->lock(doLock);
}

void ManagedObjectAdapter::lock(ManagedObject* obj) {
	((ManagedObjectImplementation*) impl)->lock(obj);
}

void ManagedObjectAdapter::rlock(bool doLock) {
	((ManagedObjectImplementation*) impl)->rlock(doLock);
}

void ManagedObjectAdapter::wlock(bool doLock) {
	((ManagedObjectImplementation*) impl)->wlock(doLock);
}

void ManagedObjectAdapter::wlock(ManagedObject* obj) {
	((ManagedObjectImplementation*) impl)->wlock(obj);
}

void ManagedObjectAdapter::unlock(bool doLock) {
	((ManagedObjectImplementation*) impl)->unlock(doLock);
}

void ManagedObjectAdapter::runlock(bool doLock) {
	((ManagedObjectImplementation*) impl)->runlock(doLock);
}

void ManagedObjectAdapter::setLockName(const String& name) {
	((ManagedObjectImplementation*) impl)->setLockName(name);
}

bool ManagedObjectAdapter::notifyDestroy() {
	return ((ManagedObjectImplementation*) impl)->notifyDestroy();
}

void ManagedObjectAdapter::initializeTransientMembers() {
	((ManagedObjectImplementation*) impl)->initializeTransientMembers();
}

void ManagedObjectAdapter::updateToDatabase() {
	((ManagedObjectImplementation*) impl)->updateToDatabase();
}

void ManagedObjectAdapter::queueUpdateToDatabaseTask() {
	((ManagedObjectImplementation*) impl)->queueUpdateToDatabaseTask();
}

void ManagedObjectAdapter::clearUpdateToDatabaseTask() {
	((ManagedObjectImplementation*) impl)->clearUpdateToDatabaseTask();
}

unsigned int ManagedObjectAdapter::getLastCRCSave() {
	return ((ManagedObjectImplementation*) impl)->getLastCRCSave();
}

void ManagedObjectAdapter::setLastCRCSave(unsigned int crc) {
	((ManagedObjectImplementation*) impl)->setLastCRCSave(crc);
}

/*
 *	ManagedObjectHelper
 */

ManagedObjectHelper* ManagedObjectHelper::staticInitializer = ManagedObjectHelper::instance();

ManagedObjectHelper::ManagedObjectHelper() {
	className = "ManagedObject";

	DistributedObjectBroker::instance()->registerClass(className, this);
}

void ManagedObjectHelper::finalizeHelper() {
	ManagedObjectHelper::finalize();
}

DistributedObject* ManagedObjectHelper::instantiateObject() {
	return new ManagedObject(DummyConstructorParameter::instance());
}

DistributedObjectServant* ManagedObjectHelper::instantiateServant() {
	return new ManagedObjectImplementation(DummyConstructorParameter::instance());
}

DistributedObjectAdapter* ManagedObjectHelper::createAdapter(DistributedObjectStub* obj) {
	DistributedObjectAdapter* adapter = new ManagedObjectAdapter((ManagedObjectImplementation*) obj->_getImplementation());

	obj->_setClassName(className);
	obj->_setClassHelper(this);

	adapter->setStub(obj);

	return adapter;
}

