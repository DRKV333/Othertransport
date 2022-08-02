#include "pch.h"

#include "LoggingRedirect.h"

#include "Addrs.h"

static void __fastcall appendHook(void* This, void*, void* event, void* pool);
static decltype(&appendHook) appendOrig = nullptr;

static void __fastcall appendHook(void* This, void*, void* event, void* pool)
{
	uintptr_t wstring = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(event) + 4) + 0x38;
	wchar_t* cstr = (reinterpret_cast<wchar_t* (__fastcall*)(uintptr_t, void*)>(*static_cast<void**>(Addrs::getptr(Addrs::wstring_cstr_ptr))))(wstring, nullptr);
	OutputDebugString(cstr);

	// TODO: Figure out why minhook fails to construct a proper trampoline here.
	//appendOrig(This, nullptr, event, pool);
}

void LoggingRedirect::initialize()
{
	MH_CreateHook(Addrs::getptr(Addrs::atlasUELogAppender_append), &appendHook, reinterpret_cast<void**>(&appendOrig));
	MH_QueueEnableHook(Addrs::getptr(Addrs::atlasUELogAppender_append));
}
