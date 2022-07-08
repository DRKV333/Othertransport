#include "pch.h"

#include "Log.h"

#include <wchar.h>
#include <malloc.h>
#include <strsafe.h>

// Stolen from https://stackoverflow.com/questions/29049686/is-there-a-better-way-to-pass-formatted-output-to-outputdebugstring
void Log::debug(const wchar_t* function, int line, const wchar_t* formatString, ...)
{
	const wchar_t* funcLineFormat = L"[%s:%d] ";

	INT cbFormatString = 0;
	va_list args;
	PWCHAR wszDebugString = nullptr;
	size_t st_Offset = 0;

	va_start(args, formatString);

	cbFormatString = _scwprintf(funcLineFormat, function, line) * sizeof(WCHAR);
	cbFormatString += _vscwprintf(formatString, args) * sizeof(WCHAR) + 2;

	/* Depending on the size of the format string, allocate space on the stack or the heap. */
	wszDebugString = (PWCHAR)_malloca(cbFormatString);

	/* Populate the buffer with the contents of the format string. */
	StringCbPrintfW(wszDebugString, cbFormatString, funcLineFormat, function, line);
	StringCbLengthW(wszDebugString, cbFormatString, &st_Offset);
	StringCbVPrintfW(&wszDebugString[st_Offset / sizeof(WCHAR)], cbFormatString - st_Offset, formatString, args);

	OutputDebugStringW(wszDebugString);

	_freea(wszDebugString);
	va_end(args);
}
