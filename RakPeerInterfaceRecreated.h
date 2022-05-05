#pragma once

#include <cstdint>

#define UNIMPLEMENTED(name) virtual void name() final { UnimplementedPurecall(#name); }

class RakPeerInterfaceRecreated
{
private:
	static void UnimplementedPurecall(const char* name);

public:
	virtual ~RakPeerInterfaceRecreated() = default;

	virtual uint32_t Startup(uint16_t maxConnections, int32_t _threadSleepTimer, void* socketDescriptor, uint32_t socketDescriptorCount, void* logger1, void* logger2) = 0;

	virtual void InitializeSecurity(void* arg1, void* arg2, int arg3, int arg4) final { } // This is called with all 0s after GetRakPeerInterface.

	UNIMPLEMENTED(DisableSecurity)
	UNIMPLEMENTED(AddToSecurityExceptionList)
	UNIMPLEMENTED(RemoveFromSecurityExceptionList)
	UNIMPLEMENTED(IsInSecurityExceptionList)

	UNIMPLEMENTED(SetMaximumIncomingConnections)
	UNIMPLEMENTED(GetMaximumIncomingConnections)

	virtual uint16_t NumberOfConnections() = 0;
	
	UNIMPLEMENTED(SetIncomingPassword)
	UNIMPLEMENTED(GetIncomingPassword)

	UNIMPLEMENTED(Connect)
	UNIMPLEMENTED(Shutdown)
	UNIMPLEMENTED(IsActive)
	UNIMPLEMENTED(GetConnectionList)

	UNIMPLEMENTED(UNKNOWN1)
	UNIMPLEMENTED(UNKNOWN2)
	UNIMPLEMENTED(UNKNOWN3)
	UNIMPLEMENTED(UNKNOWN4)
	UNIMPLEMENTED(UNKNOWN5)

	virtual void* Receive(void* arg) = 0;

	UNIMPLEMENTED(NOTSURE1)
	UNIMPLEMENTED(DeallocatePacket)

	UNIMPLEMENTED(GetMaximumNumberOfPeers)
	UNIMPLEMENTED(NOTSURE3)
	UNIMPLEMENTED(CloseConnection)
	UNIMPLEMENTED(GetConnectionState)
	UNIMPLEMENTED(CancelConnectionAttempt)
	UNIMPLEMENTED(GetIndexFromSystemAddress)
	UNIMPLEMENTED(GetSystemAddressFromIndex)
	UNIMPLEMENTED(GetUIDFromIndex)
	UNIMPLEMENTED(GetSystemList)
	UNIMPLEMENTED(AddToBanList)
	
	virtual void SetOccasionalPing(bool value) final { } // Set to true after GetRakPeerInterface.

	UNIMPLEMENTED(SetOfflinePingResponse)
	UNIMPLEMENTED(GetOfflinePingResponse)
	UNIMPLEMENTED(FUN_0174dd00)
	UNIMPLEMENTED(FUN_0174ddb0)
	UNIMPLEMENTED(GetConnectionSocketsLength)
	UNIMPLEMENTED(GetInternalID)
	UNIMPLEMENTED(FUN_0174df90)
	UNIMPLEMENTED(FUN_0174e090)

	virtual void UnknownCalledBeforeStartup2(uint32_t arg1, uint32_t arg2, uint32_t arg3) final
	{
		// This is called immediately after GetRakPeerInterface with constants (30000, 0xFFFFFFFF, 0x0000FFFF)
	}

	virtual bool UnknownCalledBeforeStartup1(uint32_t arg1, uint32_t arg2, uint32_t arg3) final
	{
		// This is called immediately after GetRakPeerInterface with constants (0x5D4, 0xFFFFFFFF, 0x0000FFFF)
		return false;
	}

	UNIMPLEMENTED(FUN_0174e320)
	UNIMPLEMENTED(GetNumberOfAddresses)
	UNIMPLEMENTED(GetLocalIP)
	UNIMPLEMENTED(IsLocalIP)
	UNIMPLEMENTED(AllowConnectionResponseIPMigration)
	UNIMPLEMENTED(SetSplitMessageProgressInterval)
	UNIMPLEMENTED(GetSplitMessageProgressInterval)
	UNIMPLEMENTED(SetUnreliableTimeout)
	UNIMPLEMENTED(SendTTL)
	UNIMPLEMENTED(SetCompileFrequencyTable)
	UNIMPLEMENTED(GetOutgoingFrequencyTable)
	UNIMPLEMENTED(FUN_0174e6d0)
	UNIMPLEMENTED(FUN_0174e760)
	UNIMPLEMENTED(FUN_0174e7f0)
	UNIMPLEMENTED(FUN_0174e850)
	UNIMPLEMENTED(AttachPlugin)
	UNIMPLEMENTED(DetachPlugin)
	UNIMPLEMENTED(PushBackPacket)
	UNIMPLEMENTED(ApplyNetworkSimulator)
	UNIMPLEMENTED(SetPerConnectionOutgoingBandwidthLimit)
	UNIMPLEMENTED(IsNetworkSimulationActive)
	
	// This is probably important, I think it might be some form of Receive, but with a SystemAddress passed to it?
	virtual uint32_t FUN_0174ea60(uint32_t arg1, uint32_t arg2) final
	{
		return 0;
	}

	UNIMPLEMENTED(FUN_0174d4c0)
	UNIMPLEMENTED(FUN_01753b40)
	UNIMPLEMENTED(FUN_01753ba0)
};

