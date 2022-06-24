#pragma once

#include "RakPeerInterfaceRecreated.h"

class DummyRakPeer : public RakPeerInterfaceRecreated
{
	uint32_t Startup(uint16_t maxConnections, int32_t _threadSleepTimer, void* socketDescriptor, uint32_t socketDescriptorCount, void* logger1, void* logger2) override;

	uint16_t NumberOfConnections() override;

	uint32_t Connect(char* host, uint16_t remotePort, char* passwordData, uint32_t passworkDataLenght, uint32_t connectionSocketIndex, uint32_t extraData) override;

	bool Send2(OLBitStreamWriter* stream, uint32_t arg2, uint32_t arg3, char arg4, uint32_t arg5, uint32_t arg6, char arg7) override;

	void* Receive(void* arg) override;

	bool CloseConnection(uint32_t arg1, uint32_t arg2, char arg3, char arg4) override;
};