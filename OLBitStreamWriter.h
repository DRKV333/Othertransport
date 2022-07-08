#pragma once

#include <cstdint>

class OLBitStreamWriter
{
private:
	OLBitStreamWriter() = delete;

public:
	uint32_t getNumberOfBytesUsed();
	char* getData();
};