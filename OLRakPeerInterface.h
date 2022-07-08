#pragma once

#include "OLRakNetTypes.h"

#include <cstdint>

#define UNIMPLEMENTED(name) virtual void name() final { unimplementedPurecall(#name); }

class OLRakPeerInterface
{
private:
	static void unimplementedPurecall(const char* name);

public:
	virtual ~OLRakPeerInterface() = default;

	virtual bool startup(uint16_t maxConnections, int32_t _threadSleepTimer, void* socketDescriptor, uint32_t socketDescriptorCount, void* logger1, void* logger2) = 0;

	virtual void initializeSecurity(void* arg1, void* arg2, int arg3, int arg4) final { } // This is called with all 0s after GetRakPeerInterface.

	UNIMPLEMENTED(disableSecurity)
	UNIMPLEMENTED(addToSecurityExceptionList)
	UNIMPLEMENTED(removeFromSecurityExceptionList)
	UNIMPLEMENTED(isInSecurityExceptionList)

	UNIMPLEMENTED(setMaximumIncomingConnections)
	UNIMPLEMENTED(getMaximumIncomingConnections)

	virtual uint16_t numberOfConnections() = 0;
	
	UNIMPLEMENTED(setIncomingPassword)
	UNIMPLEMENTED(getIncomingPassword)

	virtual bool connect(char* host, uint16_t remotePort, char* passwordData, uint32_t passworkDataLenght, uint32_t connectionSocketIndex) = 0;

	UNIMPLEMENTED(shutdown)
	UNIMPLEMENTED(isActive)
	UNIMPLEMENTED(getConnectionList)

	UNIMPLEMENTED(send1)

	virtual bool send2(class OLBitStreamWriter* stream, uint32_t arg2, uint32_t arg3, char arg4, OLSystemAddress adddress, char arg7) = 0;

	UNIMPLEMENTED(send3)
	UNIMPLEMENTED(send4)
	UNIMPLEMENTED(send5)

	virtual void* receive(void* arg) = 0;

	UNIMPLEMENTED(allocatePacket)
	UNIMPLEMENTED(deallocatePacket)

	UNIMPLEMENTED(getMaximumNumberOfPeers)
	UNIMPLEMENTED(FUN_0174d630)
	
	virtual bool isConnected(OLSystemAddress address, bool flag1, bool flag2) = 0;

	UNIMPLEMENTED(GetRemoteSystemFromSystemAddressPub)

	virtual OLSystemAddress* getSystemAddressFromIndex(OLSystemAddress* address, int index) = 0;

	UNIMPLEMENTED(FUN_0174d910)
	UNIMPLEMENTED(FUN_0174d8e0)
	UNIMPLEMENTED(getUIDFromIndex)
	UNIMPLEMENTED(getSystemList)
	UNIMPLEMENTED(addToBanList)
	
	virtual void setOccasionalPing(bool value) final { } // Set to true after GetRakPeerInterface.

	UNIMPLEMENTED(setOfflinePingResponse)
	UNIMPLEMENTED(getOfflinePingResponse)
	UNIMPLEMENTED(FUN_0174dd00)
	UNIMPLEMENTED(FUN_0174ddb0)
	UNIMPLEMENTED(getConnectionSocketsLength)
	UNIMPLEMENTED(getInternalID)
	UNIMPLEMENTED(FUN_0174df90)
	UNIMPLEMENTED(FUN_0174e090)

	virtual void unknownCalledBeforeStartup2(uint32_t arg1, uint32_t arg2, uint32_t arg3) final
	{
		// This is called immediately after GetRakPeerInterface with constants (30000, 0xFFFFFFFF, 0x0000FFFF)
	}

	virtual bool unknownCalledBeforeStartup1(uint32_t arg1, uint32_t arg2, uint32_t arg3) final
	{
		// This is called immediately after GetRakPeerInterface with constants (0x5D4, 0xFFFFFFFF, 0x0000FFFF)
		return false;
	}

	UNIMPLEMENTED(FUN_0174e320)
	UNIMPLEMENTED(getNumberOfAddresses)
	UNIMPLEMENTED(getLocalIP)
	UNIMPLEMENTED(isLocalIP)
	UNIMPLEMENTED(allowConnectionResponseIPMigration)
	UNIMPLEMENTED(setSplitMessageProgressInterval)
	UNIMPLEMENTED(getSplitMessageProgressInterval)
	UNIMPLEMENTED(setUnreliableTimeout)
	UNIMPLEMENTED(sendTTL)
	UNIMPLEMENTED(setCompileFrequencyTable)
	UNIMPLEMENTED(getOutgoingFrequencyTable)
	UNIMPLEMENTED(FUN_0174e6d0)
	UNIMPLEMENTED(FUN_0174e760)
	UNIMPLEMENTED(FUN_0174e7f0)
	UNIMPLEMENTED(FUN_0174e850)
	UNIMPLEMENTED(attachPlugin)
	UNIMPLEMENTED(detachPlugin)
	UNIMPLEMENTED(pushBackPacket)
	UNIMPLEMENTED(applyNetworkSimulator)
	UNIMPLEMENTED(setPerConnectionOutgoingBandwidthLimit)
	UNIMPLEMENTED(isNetworkSimulationActive)
	
	// This is probably important, I think it might be some form of Receive, but with a SystemAddress passed to it?
	virtual uint32_t FUN_0174ea60(uint32_t arg1, uint32_t arg2) final
	{
		return 0;
	}

	UNIMPLEMENTED(FUN_0174d4c0)
	UNIMPLEMENTED(setLogger)
	UNIMPLEMENTED(FUN_01753ba0)
};

