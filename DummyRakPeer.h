#pragma once

#include "RakPeerInterfaceRecreated.h"

class DummyRakPeer : public RakPeerInterfaceRecreated
{
	uint32_t Startup(uint16_t maxConnections, int32_t _threadSleepTimer, void* socketDescriptor, uint32_t socketDescriptorCount, void* logger1, void* logger2) override;

	uint16_t NumberOfConnections() override;

	void* Receive(void* arg) override;
};