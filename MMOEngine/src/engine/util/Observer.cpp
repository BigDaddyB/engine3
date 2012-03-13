/*
 *	engine/util/Observer.cpp generated by engine3 IDL compiler 0.60
 */

#include "Observer.h"

#include "engine/log/Logger.h"

#include "engine/util/Observable.h"

/*
 *	ObserverStub
 */

enum {RPC_NOTIFYOBSERVEREVENT__INT_OBSERVABLE_MANAGEDOBJECT_LONG_ = 6,RPC_GETOBJECTID__,RPC_COMPARETO__OBSERVER_,RPC_SETOBSERVERTYPE__INT_,RPC_ISOBSERVERTYPE__INT_};

Observer::Observer() : ManagedObject(DummyConstructorParameter::instance()) {
	ObserverImplementation* _implementation = new ObserverImplementation();
	_impl = _implementation;
	_impl->_setStub(this);
}

Observer::Observer(DummyConstructorParameter* param) : ManagedObject(param) {
}

Observer::~Observer() {
}



int Observer::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, long long arg2) {
	ObserverImplementation* _implementation = static_cast<ObserverImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_NOTIFYOBSERVEREVENT__INT_OBSERVABLE_MANAGEDOBJECT_LONG_);
		method.addUnsignedIntParameter(eventType);
		method.addObjectParameter(observable);
		method.addObjectParameter(arg1);
		method.addSignedLongParameter(arg2);

		return method.executeWithSignedIntReturn();
	} else
		return _implementation->notifyObserverEvent(eventType, observable, arg1, arg2);
}

unsigned long long Observer::getObjectID() {
	ObserverImplementation* _implementation = static_cast<ObserverImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_GETOBJECTID__);

		return method.executeWithUnsignedLongReturn();
	} else
		return _implementation->getObjectID();
}

int Observer::compareTo(Observer* obj) {
	ObserverImplementation* _implementation = static_cast<ObserverImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_COMPARETO__OBSERVER_);
		method.addObjectParameter(obj);

		return method.executeWithSignedIntReturn();
	} else
		return _implementation->compareTo(obj);
}

void Observer::setObserverType(unsigned int type) {
	ObserverImplementation* _implementation = static_cast<ObserverImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_SETOBSERVERTYPE__INT_);
		method.addUnsignedIntParameter(type);

		method.executeWithVoidReturn();
	} else
		_implementation->setObserverType(type);
}

bool Observer::isObserverType(unsigned int type) {
	ObserverImplementation* _implementation = static_cast<ObserverImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_ISOBSERVERTYPE__INT_);
		method.addUnsignedIntParameter(type);

		return method.executeWithBooleanReturn();
	} else
		return _implementation->isObserverType(type);
}

DistributedObjectServant* Observer::_getImplementation() {

	_updated = true;
	return _impl;
}

void Observer::_setImplementation(DistributedObjectServant* servant) {
	_impl = servant;
}

/*
 *	ObserverImplementation
 */

ObserverImplementation::ObserverImplementation(DummyConstructorParameter* param) : ManagedObjectImplementation(param) {
	_initializeImplementation();
}


ObserverImplementation::~ObserverImplementation() {
}


void ObserverImplementation::finalize() {
}

void ObserverImplementation::_initializeImplementation() {
	_setClassHelper(ObserverHelper::instance());

	_this = NULL;

	_serializationHelperMethod();
}

void ObserverImplementation::_setStub(DistributedObjectStub* stub) {
	_this = static_cast<Observer*>(stub);
	ManagedObjectImplementation::_setStub(stub);
}

DistributedObjectStub* ObserverImplementation::_getStub() {
	return _this;
}

ObserverImplementation::operator const Observer*() {
	return _this;
}

void ObserverImplementation::lock(bool doLock) {
	_this->lock(doLock);
}

void ObserverImplementation::lock(ManagedObject* obj) {
	_this->lock(obj);
}

void ObserverImplementation::rlock(bool doLock) {
	_this->rlock(doLock);
}

void ObserverImplementation::wlock(bool doLock) {
	_this->wlock(doLock);
}

void ObserverImplementation::wlock(ManagedObject* obj) {
	_this->wlock(obj);
}

void ObserverImplementation::unlock(bool doLock) {
	_this->unlock(doLock);
}

void ObserverImplementation::runlock(bool doLock) {
	_this->runlock(doLock);
}

void ObserverImplementation::_serializationHelperMethod() {
	ManagedObjectImplementation::_serializationHelperMethod();

	_setClassName("Observer");

}

void ObserverImplementation::readObject(ObjectInputStream* stream) {
	uint16 _varCount = stream->readShort();
	for (int i = 0; i < _varCount; ++i) {
		String _name;
		_name.parseFromBinaryStream(stream);

		uint16 _varSize = stream->readShort();

		int _currentOffset = stream->getOffset();

		if(ObserverImplementation::readObjectMember(stream, _name)) {
		}

		stream->setOffset(_currentOffset + _varSize);
	}

	initializeTransientMembers();
}

bool ObserverImplementation::readObjectMember(ObjectInputStream* stream, const String& _name) {
	if (ManagedObjectImplementation::readObjectMember(stream, _name))
		return true;

	if (_name == "Observer.observerType") {
		TypeInfo<unsigned int >::parseFromBinaryStream(&observerType, stream);
		return true;
	}


	return false;
}

void ObserverImplementation::writeObject(ObjectOutputStream* stream) {
	int _currentOffset = stream->getOffset();
	stream->writeShort(0);
	int _varCount = ObserverImplementation::writeObjectMembers(stream);
	stream->writeShort(_currentOffset, _varCount);
}

int ObserverImplementation::writeObjectMembers(ObjectOutputStream* stream) {
	String _name;
	int _offset;
	uint16 _totalSize;
	_name = "Observer.observerType";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<unsigned int >::toBinaryStream(&observerType, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);


	return 1 + ManagedObjectImplementation::writeObjectMembers(stream);
}

int ObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, long long arg2) {
	// engine/util/Observer.idl():  		return 1;
	return 1;
}

ObserverImplementation::ObserverImplementation() {
	_initializeImplementation();
	// engine/util/Observer.idl():  		observerType = 0;
	observerType = 0;
}

int ObserverImplementation::compareTo(Observer* obj) {
	// engine/util/Observer.idl():  			return 0;
	if (getObjectID() < obj->getObjectID())	// engine/util/Observer.idl():  			return 1;
	return 1;

	else 	// engine/util/Observer.idl():  			return 0;
	if (getObjectID() > obj->getObjectID())	// engine/util/Observer.idl():  			return -1;
	return -1;

	else 	// engine/util/Observer.idl():  			return 0;
	return 0;
}

void ObserverImplementation::setObserverType(unsigned int type) {
	// engine/util/Observer.idl():  		observerType = type;
	observerType = type;
}

bool ObserverImplementation::isObserverType(unsigned int type) {
	// engine/util/Observer.idl():  		return observerType == type;
	return observerType == type;
}

/*
 *	ObserverAdapter
 */

ObserverAdapter::ObserverAdapter(Observer* obj) : ManagedObjectAdapter(obj) {
}

Packet* ObserverAdapter::invokeMethod(uint32 methid, DistributedMethod* inv) {
	Packet* resp = new MethodReturnMessage(0);

	switch (methid) {
	case RPC_NOTIFYOBSERVEREVENT__INT_OBSERVABLE_MANAGEDOBJECT_LONG_:
		resp->insertSignedInt(notifyObserverEvent(inv->getUnsignedIntParameter(), static_cast<Observable*>(inv->getObjectParameter()), static_cast<ManagedObject*>(inv->getObjectParameter()), inv->getSignedLongParameter()));
		break;
	case RPC_GETOBJECTID__:
		resp->insertLong(getObjectID());
		break;
	case RPC_COMPARETO__OBSERVER_:
		resp->insertSignedInt(compareTo(static_cast<Observer*>(inv->getObjectParameter())));
		break;
	case RPC_SETOBSERVERTYPE__INT_:
		setObserverType(inv->getUnsignedIntParameter());
		break;
	case RPC_ISOBSERVERTYPE__INT_:
		resp->insertBoolean(isObserverType(inv->getUnsignedIntParameter()));
		break;
	default:
		return NULL;
	}

	return resp;
}

int ObserverAdapter::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, long long arg2) {
	return (static_cast<Observer*>(stub))->notifyObserverEvent(eventType, observable, arg1, arg2);
}

unsigned long long ObserverAdapter::getObjectID() {
	return (static_cast<Observer*>(stub))->getObjectID();
}

int ObserverAdapter::compareTo(Observer* obj) {
	return (static_cast<Observer*>(stub))->compareTo(obj);
}

void ObserverAdapter::setObserverType(unsigned int type) {
	(static_cast<Observer*>(stub))->setObserverType(type);
}

bool ObserverAdapter::isObserverType(unsigned int type) {
	return (static_cast<Observer*>(stub))->isObserverType(type);
}

/*
 *	ObserverHelper
 */

ObserverHelper* ObserverHelper::staticInitializer = ObserverHelper::instance();

ObserverHelper::ObserverHelper() {
	className = "Observer";

	Core::getObjectBroker()->registerClass(className, this);
}

void ObserverHelper::finalizeHelper() {
	ObserverHelper::finalize();
}

DistributedObject* ObserverHelper::instantiateObject() {
	return new Observer(DummyConstructorParameter::instance());
}

DistributedObjectServant* ObserverHelper::instantiateServant() {
	return new ObserverImplementation(DummyConstructorParameter::instance());
}

DistributedObjectAdapter* ObserverHelper::createAdapter(DistributedObjectStub* obj) {
	DistributedObjectAdapter* adapter = new ObserverAdapter(static_cast<Observer*>(obj));

	obj->_setClassName(className);
	obj->_setClassHelper(this);

	adapter->setStub(obj);

	return adapter;
}

