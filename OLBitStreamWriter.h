#pragma once

#include <cstdint>

class OLBitStreamWriter
{
private:
	OLBitStreamWriter() = default;

public:
	uint32_t getNumberOfBytesUsed();
	char* getData();
};