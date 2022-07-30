#include "pch.h"

#include "OLRakPeerAdapter.h"

#include "Log.h"
#include "Addrs.h"
#include "AsyncSocket.h"

uint16_t OLRakPeerAdapter::numberOfConnections()
{
	return connected ? 1 : 0;
}

bool OLRakPeerAdapter::connect(char* host, uint16_t remotePort, char* passwordData, uint32_t passworkDataLenght, uint32_t connectionSocketIndex)
{
	LOG_DEBUG(L"[%X] %S:%u", this, host, remotePort);

	if (connected)
	{
		LOG_DEBUG(L"[%X] Already connected to %X:%u", this, thePacket.systemAddress.ip, thePacket.systemAddress.port);
		return false;
	}
	
	uint32_t ip[2];
	reinterpret_cast<void(__cdecl*)(uint32_t*, char*)>(Addrs::getptr(Addrs::parseIpV4))(ip, host);

	thePacket.systemIndex = connectedSystemIndex;
	thePacket.systemAddress.ip = ip[0];
	thePacket.systemAddress.port = remotePort;
	thePacket.systemGUID = connectedGUID;

	socket->connect(ip[0], remotePort);

	return true;
}

bool OLRakPeerAdapter::send2(OLBitStream* stream, uint32_t arg2, uint32_t arg3, char arg4, OLSystemAddress address, char arg7)
{
	if (!connected)
	{
		LOG_DEBUG(L"Not connected");
		return false;
	}

	if (address != thePacket.systemAddress)
	{
		LOG_DEBUG(L"Message sent to wrong address: %X:%u", address.ip, address.port);
		return false;
	}

	socket->send(stream->data, stream->getNumberOfBytesUsed());
	return true;
}

OLPacket* OLRakPeerAdapter::receive(void* arg)
{
	if (thePacketWasReceived)
	{
		LOG_DEBUG(L"Receive was called before deallocate.");
		return nullptr;
	}

	uint32_t length;
	char* data = socket->receive(&length);

	if (data == nullptr)
		return nullptr;

	if (length == 1 && data[0] == OLDefaultMessageIDTypes::OL_ID_CONNECTION_REQUEST_ACCEPTED)
		connected = true;

	thePacket.data = data;
	thePacket.length = length;
	thePacket.lengthBits = length * 8;

	thePacketWasReceived = true;
	return &thePacket;
}

void OLRakPeerAdapter::deallocatePacket(OLPacket* packet)
{
	if (packet != &thePacket)
	{
		LOG_DEBUG(L"[%X] Tried to deallocate invalid packet: %X", this, packet);
		return;
	}

	if (!thePacketWasReceived)
	{
		LOG_DEBUG(L"[%X] Packet was not sent before deallocate.");
		return;
	}

	socket->receiveAck();
	thePacketWasReceived = false;
}

bool OLRakPeerAdapter::isConnected(OLSystemAddress address, bool flag1, bool flag2)
{
	LOG_DEBUG(L"[%X] %X:%u", this, address.ip, address.port);	
	return connected && address == thePacket.systemAddress;
}

OLSystemAddress* OLRakPeerAdapter::getSystemAddressFromIndex(OLSystemAddress* address, int index)
{
	if (connected && index == 0)
		*address = thePacket.systemAddress;
	else
		*address = OLSystemAddress::unassigned;
	return address;
}
