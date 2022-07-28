#pragma once

#include "OLRakPeerInterface.h"

#include <memory>

class OLRakPeerAdapter : public OLRakPeerInterface
{
private:
	bool connected = false;
	
	OLPacket thePacket{
		OLPacket::unassignedSystemIndex,
		OLSystemAddress::unassigned,
		OLRakNetGUID::unassigned,
		0, 0, nullptr, false
	};
	bool thePacketWasReceived = false;

	static constexpr OLRakNetGUID connectedGUID = { 0x01, 0x00, 0x00, 0x00 };
	static constexpr uint16_t connectedSystemIndex = 0;

	std::unique_ptr<class AsyncSocket> socket;

public:
	explicit OLRakPeerAdapter(std::unique_ptr<class AsyncSocket> socket) : socket(std::move(socket)) { }

	virtual uint16_t numberOfConnections() override;

	virtual bool connect(char* host, uint16_t remotePort, char* passwordData, uint32_t passworkDataLenght, uint32_t connectionSocketIndex) override;

	virtual bool send2(OLBitStream* stream, uint32_t arg2, uint32_t arg3, char arg4, OLSystemAddress address, char arg7) override;

	virtual OLPacket* receive(void* arg) override;

	virtual void deallocatePacket(OLPacket* packet) override;

	virtual bool isConnected(OLSystemAddress address, bool flag1, bool flag2) override;

	virtual OLSystemAddress* getSystemAddressFromIndex(OLSystemAddress* address, int index) override;
};