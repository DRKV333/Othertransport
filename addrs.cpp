#include "pch.h"

#include "addrs.h"

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

DEFTABLE(addrs::table_t, test32,
{
	$[addrs::base]                    = 0x00400000;
	$[addrs::winMain]                 = 0x01137910;
	$[addrs::getRakPeerInterface]     = 0x01747550;
	$[addrs::destroyRakPeerInterface] = 0x01747560;
})

void addrs::Initialize()
{
	current = test32;

	HMODULE mainModule = GetModuleHandleA("Otherland-Test.exe");
	intptr_t baseOffset = reinterpret_cast<uintptr_t>(mainModule) - current[addrs::base];

	for (uintptr_t& ptr : current)
	{
		ptr += baseOffset;
	}
}