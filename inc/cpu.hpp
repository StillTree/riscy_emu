#pragma once

#include "typedefs.hpp"
#include <array>

namespace riscy_emu {

struct cpu_state {
	std::array<i64, 32> registers { };
	u64 pc { 0 };

private:
	auto set_reg(usz reg, i64 val);
	auto get_reg(usz reg) -> i64;
};

}
