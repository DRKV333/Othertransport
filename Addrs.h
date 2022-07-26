#pragma once

#include <array>

class Addrs
{
public:
	enum addrId
	{
		base,
		unrealMain,
		getRakPeerInterface,
		destroyRakPeerInterface,
		parseIpV4,

		ADDRID_SIZE
	};

	using table_t = std::array<uintptr_t, ADDRID_SIZE>;

private:
	static inline table_t current;

public:
	static uintptr_t get(addrId id) { return current[id]; }
	static void* getptr(addrId id) { return reinterpret_cast<void*>(current[id]); }
	static void initialize();
};
