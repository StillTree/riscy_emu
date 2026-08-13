#include <print>

#include "cpu.hpp"
#include "typedefs.hpp"
#include "mem_bus.hpp"

auto main() -> riscy_emu::i32
{
	riscy_emu::mem_bus a;
	riscy_emu::cpu_state cpu;

	std::println("Hello, World!");
}
