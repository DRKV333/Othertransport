#include "pch.h"

#include "Addrs.h"

#include <algorithm>

#define DEFTABLE(TYPE, NAME, INITER)                                \
static constexpr TYPE NAME = []()                                   \
{                                                                   \
	auto $ = TYPE();                                                \
	INITER                                                          \
	return $;                                                       \
}();                                                                \
static_assert(std::ranges::find(NAME, 0) == std::ranges::end(NAME), \
	"Every address must be specified.");                            \

DEFTABLE(Addrs::table_t, test32,
{
	$[Addrs::base]                    = 0x00400000;
	$[Addrs::winMain]                 = 0x01137910;
	$[Addrs::getRakPeerInterface]     = 0x01747550;
	$[Addrs::destroyRakPeerInterface] = 0x01747560;
})

void Addrs::initialize()
{
	current = test32;

	HMODULE mainModule = GetModuleHandleA("Otherland-Test.exe");
	intptr_t baseOffset = reinterpret_cast<uintptr_t>(mainModule) - current[Addrs::base];

	for (uintptr_t& ptr : current)
	{
		ptr += baseOffset;
	}
}