#pragma once

#include "RakPeerInterfaceRecreated.h"

class DummyRakPeer : public RakPeerInterfaceRecreated
{
private:
	bool connected = false;

public:
	virtual bool Startup(uint16_t maxConnections, int32_t _threadSleepTimer, void* socketDescriptor, uint32_t socketDescriptorCount, void* logger1, void* logger2) override;

	virtual uint16_t NumberOfConnections() override;

	virtual bool Connect(char* host, uint16_t remotePort, char* passwordData, uint32_t passworkDataLenght, uint32_t connectionSocketIndex) override;

	virtual bool Send2(class OLBitStreamWriter* stream, uint32_t arg2, uint32_t arg3, char arg4, uint32_t arg5, uint32_t arg6, char arg7) override;

	virtual void* Receive(void* arg) override;

	virtual bool IsConnected(OLSystemAddress address, bool flag1, bool flag2) override;
};