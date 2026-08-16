#include <print>

#include "machine.hpp"
#include "typedefs.hpp"

auto main() -> riscy_emu::i32
{
	riscy_emu::machine m;
	m.run();
	std::println("Hello, World!");
}
