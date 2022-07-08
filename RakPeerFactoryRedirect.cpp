#include "pch.h"

#include "RakPeerFactoryRedirect.h"

#include "Addrs.h"
#include "DummyRakPeer.h"
#include "Log.h"

static OLRakPeerInterface* __stdcall GetRakPeerInterface()
{
	OLRakPeerInterface* rakPeer = new DummyRakPeer();
	LOG_DEBUG(L"Created RakPeer: %X", rakPeer);
	return rakPeer;
}

static void __stdcall DestroyRakPeerInterface(OLRakPeerInterface* rakPeer)
{
	delete rakPeer;
	LOG_DEBUG(L"Destroyed RakPeer: %X", rakPeer);
}

void RakPeerFactoryRedirect::initialize()
{
	MH_CreateHook(Addrs::getptr(Addrs::getRakPeerInterface), &GetRakPeerInterface, nullptr);
	MH_CreateHook(Addrs::getptr(Addrs::destroyRakPeerInterface), &DestroyRakPeerInterface, nullptr);
	MH_QueueEnableHook(Addrs::getptr(Addrs::getRakPeerInterface));
	MH_QueueEnableHook(Addrs::getptr(Addrs::destroyRakPeerInterface));
}