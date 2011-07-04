/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/


#include "BasePacketChekupEvent.h"

#include "BaseClientNetStatusCheckupEvent.h"
#include "BaseClientCleanupEvent.h"
#include "BaseClientNetStatusRequestEvent.h"
#include "BaseClientEvent.h"

BasePacketChekupEvent::BasePacketChekupEvent(BaseClient* cl, uint32 time) : Task(time) {
	client = cl;
	checkupTime = time;
}

void BasePacketChekupEvent::run() {
	client->checkupServerPackets(packet);
}
