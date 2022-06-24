#include "pch.h"
#include "OLBitStreamWriter.h"

template <typename T, intptr_t offest>
T getAtOffset(void* src)
{
    uintptr_t ptr = reinterpret_cast<uintptr_t>(src) + offest;
    return *reinterpret_cast<T*>(ptr);
}

uint32_t OLBitStreamWriter::getNumberOfBytesUsed()
{
    return (getAtOffset<uint32_t, 0>(this) + 7) >> 3;
}

char* OLBitStreamWriter::getData()
{
    return getAtOffset<char*, 12>(this);
}
