#include "pch.h"

#include "Addrs.h"
#include "RakPeerFactoryRedirect.h"

static INT __cdecl mainHook(LPWSTR cmdlinew, HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline);
static decltype(&mainHook) mainOrig = nullptr;

static INT __cdecl mainHook(LPWSTR cmdlinew, HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline)
{
    RakPeerFactoryRedirect::initializePostMain();
    return mainOrig(cmdlinew, hInst, hInstPrev, cmdline);
}

static void installMainHook()
{
    MH_CreateHook(Addrs::getptr(Addrs::unrealMain), &mainHook, reinterpret_cast<void**>(&mainOrig));
    MH_QueueEnableHook(Addrs::getptr(Addrs::unrealMain));
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        Addrs::initialize();
        MH_Initialize();
        installMainHook();
        RakPeerFactoryRedirect::initialize();
        MH_ApplyQueued();
    }

    return TRUE;
}