#include "pch.h"

#include "DummyRakPeer.h"

#include "OLBitStreamWriter.h"
#include "Log.h"
#include "Addrs.h"

bool DummyRakPeer::startup(uint16_t maxConnections, int32_t _threadSleepTimer, void* socketDescriptor, uint32_t socketDescriptorCount, void* logger1, void* logger2)
{
	LOG_DEBUG(L"[%X] maxConnections: %u, _threadSleepTimer: %d, socketDescriptorCount: %u", this, maxConnections, _threadSleepTimer, socketDescriptorCount);
	return true; // Weirdly, a 0 here indicates failure.
}

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
		thePacket.systemIndex = 0;
		thePacket.systemAddress.port = remotePort;
		thePacket.systemGUID = connectedGUID;

		reinterpret_cast<void(__cdecl*)(uint32_t*, char*)>(Addrs::getptr(Addrs::parseIpV4))(&thePacket.systemAddress.ip, host);
	
		connected = true;
		pendingConnectMessage = true;
		return true;
	}
}

bool DummyRakPeer::send2(OLBitStreamWriter* stream, uint32_t arg2, uint32_t arg3, char arg4, OLSystemAddress adddress, char arg7)
{
	LOG_DEBUG(L"[%X] data: %X, length: %u, address: %X:%u", this, stream->getData(), stream->getNumberOfBytesUsed(), adddress.ip, adddress.port);
	return true;
}

OLPacket* DummyRakPeer::receive(void* arg)
{
	if (thePacketWasReceived)
	{
		LOG_DEBUG(L"Receive was called before deallocate.");
		return nullptr;
	}

	if (pendingConnectMessage)
	{
		thePacket.length = 1;
		thePacket.lengthBits = 1 * 8;

		thePacket.data = &connectMessage;

		pendingConnectMessage = false;
		thePacketWasReceived = true;
		LOG_DEBUG(L"Received connect message");
		return &thePacket;
	}

	return nullptr;
}

void DummyRakPeer::deallocatePacket(OLPacket* packet)
{
	if (packet != &thePacket)
		LOG_DEBUG(L"[%X] Tried to deallocate invalid packet: %X", this, packet);
	else if (!thePacketWasReceived)
		LOG_DEBUG(L"[%X] Packet was not sent before deallocate.");
	else
		thePacketWasReceived = false;
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
