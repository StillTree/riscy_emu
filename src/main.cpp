#include <print>

#include "machine.hpp"
#include "typedefs.hpp"

auto main() -> riscy_emu::i32
{
	std::println("riscy_emu v{}", RISCY_VERSION);

	riscy_emu::machine m;
	m.run();
}
