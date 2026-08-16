#include "hart.hpp"

#include "typedefs.hpp"

namespace riscy_emu {

hart_state::hart_state(mem_bus* bus)
	: bus(bus)
{
}

auto hart_state::step() -> void { }

auto hart_state::set_reg(usz reg, i64 val) -> void
{
	if (reg <= 0) {
		return;
	}

	registers[reg] = val;
}

auto hart_state::get_reg(usz reg) -> i64
{
	return registers[reg];
}

}
