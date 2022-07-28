#include "pch.h"

#include "DummyRakPeer.h"

#include "Log.h"
#include "Addrs.h"
#include "AsyncSocket.h"

uint16_t DummyRakPeer::numberOfConnections()
{
	return connected ? 1 : 0;
}

bool DummyRakPeer::connect(char* host, uint16_t remotePort, char* passwordData, uint32_t passworkDataLenght, uint32_t connectionSocketIndex)
{
	LOG_DEBUG(L"[%X] %S:%u", this, host, remotePort);

	if (connected)
	{
		LOG_DEBUG(L"[%X] Already connected to %X:%u", this, thePacket.systemAddress.ip, thePacket.systemAddress.port);
		return false;
	}
	else
	{
		uint32_t ip[2];
		reinterpret_cast<void(__cdecl*)(uint32_t*, char*)>(Addrs::getptr(Addrs::parseIpV4))(ip, host);

		thePacket.systemIndex = connectedSystemIndex;
		thePacket.systemAddress.ip = ip[0];
		thePacket.systemAddress.port = remotePort;
		thePacket.systemGUID = connectedGUID;

		socket->connect(ip[0], remotePort);

		connected = true;
		return true;
	}
}

bool DummyRakPeer::send2(OLBitStream* stream, uint32_t arg2, uint32_t arg3, char arg4, OLSystemAddress address, char arg7)
{
	if (address == thePacket.systemAddress)
	{
		socket->send(stream->data, stream->getNumberOfBytesUsed());
		return true;
	}
	else
	{
		LOG_DEBUG(L"Message sent to wrong address: %X:%u", address.ip, address.port);
		return false;
	}
}

OLPacket* DummyRakPeer::receive(void* arg)
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

	thePacket.data = data;
	thePacket.length = length;
	thePacket.lengthBits = length * 8;

	thePacketWasReceived = true;
	return &thePacket;
}

void DummyRakPeer::deallocatePacket(OLPacket* packet)
{
	if (packet != &thePacket)
	{
		LOG_DEBUG(L"[%X] Tried to deallocate invalid packet: %X", this, packet);
	}
	else if (!thePacketWasReceived)
	{
		LOG_DEBUG(L"[%X] Packet was not sent before deallocate.");
	}
	else
	{
		socket->receiveAck();
		thePacketWasReceived = false;
	}
}

bool DummyRakPeer::isConnected(OLSystemAddress address, bool flag1, bool flag2)
{
	LOG_DEBUG(L"[%X] %X:%u", this, address.ip, address.port);	
	return connected && address == thePacket.systemAddress;
}

OLSystemAddress* DummyRakPeer::getSystemAddressFromIndex(OLSystemAddress* address, int index)
{
	if (connected && index == 0)
		*address = thePacket.systemAddress;
	else
		*address = OLSystemAddress::unassigned;
	return address;
}
