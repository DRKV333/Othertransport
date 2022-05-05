#include "pch.h"

#include "RakPeerFactoryRedirect.h"

#include "addrs.h"
#include "DummyRakPeer.h"

static RakPeerInterfaceRecreated* __stdcall GetRakPeerInterface()
{
	return new DummyRakPeer();
}

static void __stdcall DestroyRakPeerInterface(RakPeerInterfaceRecreated* rakPeer)
{
	delete rakPeer;
}

void RakPeerFactoryRedirect::Initialize()
{
	MH_CreateHook(addrs::getptr(addrs::getRakPeerInterface), &GetRakPeerInterface, nullptr);
	MH_CreateHook(addrs::getptr(addrs::destroyRakPeerInterface), &DestroyRakPeerInterface, nullptr);
	MH_QueueEnableHook(addrs::getptr(addrs::getRakPeerInterface));
	MH_QueueEnableHook(addrs::getptr(addrs::destroyRakPeerInterface));
}