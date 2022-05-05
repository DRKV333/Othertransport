#include "pch.h"

#include "DummyRakPeer.h"

#include <wchar.h>
#include <malloc.h>
#include <strsafe.h>

// Stolen from https://stackoverflow.com/questions/29049686/is-there-a-better-way-to-pass-formatted-output-to-outputdebugstring
#ifdef _DEBUG
#define DBGPRINT(kwszDebugFormatString, ...) _DBGPRINT(__FUNCTIONW__, __LINE__, kwszDebugFormatString __VA_OPT__ (,) __VA_ARGS__)

VOID _DBGPRINT(LPCWSTR kwszFunction, INT iLineNumber, LPCWSTR kwszDebugFormatString, ...) \
{
	INT cbFormatString = 0;
	va_list args;
	PWCHAR wszDebugString = NULL;
	size_t st_Offset = 0;

	va_start(args, kwszDebugFormatString);

	cbFormatString = _scwprintf(L"[%s:%d] ", kwszFunction, iLineNumber) * sizeof(WCHAR);
	cbFormatString += _vscwprintf(kwszDebugFormatString, args) * sizeof(WCHAR) + 2;

	/* Depending on the size of the format string, allocate space on the stack or the heap. */
	wszDebugString = (PWCHAR)_malloca(cbFormatString);

	/* Populate the buffer with the contents of the format string. */
	StringCbPrintfW(wszDebugString, cbFormatString, L"[%s:%d] ", kwszFunction, iLineNumber);
	StringCbLengthW(wszDebugString, cbFormatString, &st_Offset);
	StringCbVPrintfW(&wszDebugString[st_Offset / sizeof(WCHAR)], cbFormatString - st_Offset, kwszDebugFormatString, args);

	OutputDebugStringW(wszDebugString);

	_freea(wszDebugString);
	va_end(args);
}
#else
#define DBGPRINT( kwszDebugFormatString, ... ) ;;
#endif

uint32_t DummyRakPeer::Startup(uint16_t maxConnections, int32_t _threadSleepTimer, void* socketDescriptor, uint32_t socketDescriptorCount, void* logger1, void* logger2)
{
	DBGPRINT(L"maxConnections: %u, _threadSleepTimer: %d, socketDescriptorCount: %u", maxConnections, _threadSleepTimer, socketDescriptor);
	return 1; // Weirdly, a 0 here indicates failure.
}

uint16_t DummyRakPeer::NumberOfConnections()
{
	DBGPRINT(L"There are no connections...");
	return 0;
}

void* DummyRakPeer::Receive(void* arg)
{
	DBGPRINT(L"You have no new messages...");
	return nullptr;
}
