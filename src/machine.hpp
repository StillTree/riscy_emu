#pragma once

#include "hart.hpp"
#include "mem_bus.hpp"
#include "typedefs.hpp"

namespace riscy_emu {

class machine {
public:
	auto run() -> void;

private:
	hart_state hart;
	mem_bus bus;
	usz cycle_num;
};

}
