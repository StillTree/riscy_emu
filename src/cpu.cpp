#include "cpu.hpp"

namespace riscy_emu {

auto cpu_state::set_reg(size_t reg, int64_t val)
{
	if (reg <= 0) {
		return;
	}

	registers[reg] = val;
}

auto cpu_state::get_reg(size_t reg) -> int64_t
{
	return registers[reg];
}

}
