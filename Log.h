#pragma once

#define LOG_DEBUG(formatString, ...) Log::debug(__FUNCTIONW__, __LINE__, formatString __VA_OPT__ (,) __VA_ARGS__)

class Log
{
private:
	Log() = delete;

public:
	static void debug(const wchar_t* function, int line, const wchar_t* formatString, ...);
};