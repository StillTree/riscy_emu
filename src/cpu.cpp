#include "cpu.hpp"

#include "typedefs.hpp"

namespace riscy_emu {

auto cpu_state::set_reg(usz reg, i64 val)
{
	if (reg <= 0) {
		return;
	}

	registers[reg] = val;
}

auto cpu_state::get_reg(usz reg) -> i64
{
	return registers[reg];
}

}
