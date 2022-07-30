#include "pch.h"

#include "RakPeerFactoryRedirect.h"

#include "Addrs.h"
#include "OLRakPeerAdapter.h"
#include "TCPSocket.h"
#include "Log.h"

static asio::io_context context;
asio::executor_work_guard<asio::io_context::executor_type> guard(context.get_executor());

static OLRakPeerInterface* __stdcall getRakPeerInterface()
{
	OLRakPeerInterface* rakPeer = new OLRakPeerAdapter(std::make_unique<TCPSocket>(context));
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

void RakPeerFactoryRedirect::initializePostMain()
{
	asio::thread ioThread([]() { context.run(); LOG_DEBUG(L"Oh no, the io thread stopped."); });
}
