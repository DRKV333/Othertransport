#include "pch.h"

#include "RakPeerFactoryRedirect.h"

#include "Addrs.h"
#include "DummyRakPeer.h"
#include "DummySocket.h"
#include "Log.h"

static OLRakPeerInterface* __stdcall getRakPeerInterface()
{
	OLRakPeerInterface* rakPeer = new DummyRakPeer(std::make_unique<DummySocket>());
	LOG_DEBUG(L"Created RakPeer: %X", rakPeer);
	return rakPeer;
}

static void __stdcall destroyRakPeerInterface(OLRakPeerInterface* rakPeer)
{
	delete rakPeer;
	LOG_DEBUG(L"Destroyed RakPeer: %X", rakPeer);
}

void RakPeerFactoryRedirect::initialize()
{
	MH_CreateHook(Addrs::getptr(Addrs::getRakPeerInterface), &getRakPeerInterface, nullptr);
	MH_CreateHook(Addrs::getptr(Addrs::destroyRakPeerInterface), &destroyRakPeerInterface, nullptr);
	MH_QueueEnableHook(Addrs::getptr(Addrs::getRakPeerInterface));
	MH_QueueEnableHook(Addrs::getptr(Addrs::destroyRakPeerInterface));
}