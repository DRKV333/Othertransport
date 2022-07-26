#pragma once

#include "OLRakPeerInterface.h"

class DummyRakPeer : public OLRakPeerInterface
{
private:
	bool connected = false;
	bool pendingConnectMessage = false;

	OLPacket thePacket{
		OLPacket::unassignedSystemIndex,
		OLSystemAddress::unassigned,
		OLRakNetGUID::unassigned,
		0, 0, nullptr, false
	};
	bool thePacketWasReceived = false;

	char connectMessage = OLDefaultMessageIDTypes::OL_ID_CONNECTION_REQUEST_ACCEPTED;

	static constexpr OLRakNetGUID connectedGUID = { 0x01, 0x00, 0x00, 0x00 };

public:
	virtual bool startup(uint16_t maxConnections, int32_t _threadSleepTimer, void* socketDescriptor, uint32_t socketDescriptorCount, void* logger1, void* logger2) override;

	virtual uint16_t numberOfConnections() override;

	virtual bool connect(char* host, uint16_t remotePort, char* passwordData, uint32_t passworkDataLenght, uint32_t connectionSocketIndex) override;

	virtual bool send2(OLBitStream* stream, uint32_t arg2, uint32_t arg3, char arg4, OLSystemAddress adddress, char arg7) override;

	virtual OLPacket* receive(void* arg) override;

	virtual void deallocatePacket(OLPacket* packet) override;

	virtual bool isConnected(OLSystemAddress address, bool flag1, bool flag2) override;

	virtual OLSystemAddress* getSystemAddressFromIndex(OLSystemAddress* address, int index) override;
};