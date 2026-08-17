#pragma once

#include "hart.hpp"
#include "mem_bus.hpp"
#include "typedefs.hpp"

namespace riscy_emu {

class machine {
public:
	machine() = default;
	machine(const machine&) = delete;
	auto operator=(const machine&) -> machine& = delete;
	machine(machine&&) = delete;
	auto operator=(machine&&) -> machine& = delete;

	auto run() -> void;

private:
	mem_bus bus;
	hart_state hart { &bus };
	usz cycle_num { 0 };
};

}
