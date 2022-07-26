#pragma once

#include <cstdint>
#include <cstddef>
#include <type_traits>

struct OLSystemAddress
{
	uint32_t ip;
	uint16_t port;

	bool operator==(const OLSystemAddress&) const = default;

	static const OLSystemAddress unassigned;
};

inline constexpr OLSystemAddress OLSystemAddress::unassigned = { 0xFFFFFFFF, 0xFFFF };

static_assert(sizeof(OLSystemAddress) == 8);
static_assert(std::is_standard_layout_v<OLSystemAddress>);
static_assert(offsetof(OLSystemAddress, ip)   == 0);
static_assert(offsetof(OLSystemAddress, port) == 4);

struct OLRakNetGUID
{
	uint32_t g[4];

	static const OLRakNetGUID unassigned;
};

inline constexpr OLRakNetGUID OLRakNetGUID::unassigned = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

static_assert(sizeof(OLRakNetGUID) == 16);
static_assert(std::is_standard_layout_v<OLRakNetGUID>);

struct OLPacket
{
	uint16_t systemIndex;
	OLSystemAddress systemAddress;
	OLRakNetGUID systemGUID;
	uint32_t length;
	uint32_t lengthBits;
	char* data;
	bool deleteData;

	static const uint16_t unassignedSystemIndex;
};

inline constexpr uint16_t OLPacket::unassignedSystemIndex = 0xFFFF;

static_assert(sizeof(OLPacket) == 44);
static_assert(std::is_standard_layout_v<OLPacket>);
static_assert(offsetof(OLPacket, systemIndex)   == 0);
static_assert(offsetof(OLPacket, systemAddress) == 4);
static_assert(offsetof(OLPacket, systemGUID)    == 12);
static_assert(offsetof(OLPacket, length)        == 28);
static_assert(offsetof(OLPacket, lengthBits)    == 32);
static_assert(offsetof(OLPacket, data)          == 36);
static_assert(offsetof(OLPacket, deleteData)    == 40);

enum OLDefaultMessageIDTypes : char
{
	OL_ID_CONNECTION_REQUEST_ACCEPTED = 0x0B,
	OL_ID_CONNECTION_ATTEMPT_FAILED = 0x0C
};