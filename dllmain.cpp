#include "pch.h"

#include "addrs.h"
#include "RakPeerFactoryRedirect.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        addrs::Initialize();
        MH_Initialize();
        RakPeerFactoryRedirect::Initialize();
        MH_ApplyQueued();
    }

    return TRUE;
}

