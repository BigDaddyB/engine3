/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef LOCALOBJECTMANAGER_H_
#define LOCALOBJECTMANAGER_H_

#include "system/lang.h"

#include "engine/orb/ObjectBroker.h"
#include "engine/orb/DistributedObjectBroker.h"

#include "engine/orb/NamingDirectoryServiceImpl.h"

#include "engine/log/Logger.h"

namespace engine {
  namespace stm {

  	class LocalObjectManager : public ObjectBroker, public Logger {
  		DistributedObjectBroker* objectBroker;
  		DOBObjectManager* objectManager;

  		HashTable<uint64, Reference<DistributedObjectStub*> > localObjectDirectory;

  		HashTable<String, Reference<DistributedObjectStub*> > localNamingDirectory;

  		SortedVector<Reference<DistributedObjectStub*> > undeployedObjects;
  		SortedVector<Reference<DistributedObjectStub*> > destroyedObjects;

  	public:
  		LocalObjectManager();

  		void commitObjectChanges();

  		void clearObjectChanges();

		void registerClass(const String& name, DistributedObjectClassHelper* helper);

		// deployment methods
		void deploy(DistributedObjectStub* obj);
		void deploy(const String& name, DistributedObjectStub* obj);

		DistributedObjectStub* undeploy(const String& name);

		DistributedObject* lookUp(const String& name);
		DistributedObject* lookUp(uint64 objid);

		bool destroyObject(DistributedObjectStub* obj);
  	};

  } // namespace stm
} // namespace engine

using namespace engine::stm;

#endif /* LOCALOBJECTMANAGER_H_ */
