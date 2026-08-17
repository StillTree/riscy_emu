#include "hart.hpp"

#include "decode.hpp"
#include "typedefs.hpp"

namespace riscy_emu {

hart_state::hart_state(mem_bus* bus)
	: bus(bus)
{
}

auto hart_state::handle_trap(trap_cause cause) -> void
{
	pc = csr.handle_trap(cause);
}

auto hart_state::step() -> void
{
	auto inst = bus->read<u32>(pc);
	if (!inst) {
		handle_trap(trap_cause::inst_access_fault);
		return;
	}

	auto handler = decode_inst(*inst);
	handler(*this, *inst);

	pc += 4;
}

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
