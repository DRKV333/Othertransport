#include "pch.h"

#include "DummyRakPeer.h"

#include "OLBitStreamWriter.h"
#include "Log.h"

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
	connected = true;
	return true;
}

bool DummyRakPeer::send2(OLBitStreamWriter* stream, uint32_t arg2, uint32_t arg3, char arg4, uint32_t arg5, uint32_t arg6, char arg7)
{
	LOG_DEBUG(L"[%X] data: %X, length: %u", this, stream->getData(), stream->getNumberOfBytesUsed());
	return true;
}

void* DummyRakPeer::receive(void* arg)
{
	return nullptr;
}

bool DummyRakPeer::isConnected(OLSystemAddress address, bool flag1, bool flag2)
{
	LOG_DEBUG(L"[%X] %X:%u", this, address.ip, address.port);
	return connected;
}
