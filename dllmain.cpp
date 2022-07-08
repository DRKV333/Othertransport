#include "pch.h"

#include "Addrs.h"
#include "RakPeerFactoryRedirect.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        Addrs::initialize();
        MH_Initialize();
        RakPeerFactoryRedirect::initialize();
        MH_ApplyQueued();
    }

    return TRUE;
}