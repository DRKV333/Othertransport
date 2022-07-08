#pragma once

#include <cstdint>
#include <cstddef>

struct OLSystemAddress
{
	unsigned char ip[4];
	uint16_t port;
};

static_assert(sizeof(OLSystemAddress) == 6);
static_assert(offsetof(OLSystemAddress, ip)   == 0);
static_assert(offsetof(OLSystemAddress, port) == 4);

struct OLRakNetGUID
{
	uint32_t g[4];
};

static_assert(sizeof(OLRakNetGUID) == 16);

struct OLPacket
{
	uint16_t systemIndex;
	alignas(4) OLSystemAddress systemAddress;
	OLRakNetGUID systemGUID;
	uint32_t length;
	uint32_t lengthBits;
	char* data;
	bool deleteData;
};

static_assert(sizeof(OLPacket) == 44);
static_assert(offsetof(OLPacket, systemIndex)   == 0);
static_assert(offsetof(OLPacket, systemAddress) == 4);
static_assert(offsetof(OLPacket, systemGUID)    == 12);
static_assert(offsetof(OLPacket, length)        == 28);
static_assert(offsetof(OLPacket, lengthBits)    == 32);
static_assert(offsetof(OLPacket, data)          == 36);
static_assert(offsetof(OLPacket, deleteData)    == 40);

constexpr OLRakNetGUID OL_UNASSIGNED_GUID = { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF };
constexpr uint16_t OL_UNASSINED_SYSTEM_INDEX = 0xFF;
