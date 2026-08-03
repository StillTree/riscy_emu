#pragma once

#include "csr.hpp"
#include "typedefs.hpp"

#include <array>

namespace riscy_emu {

struct cpu_state {
	auto set_reg(usz reg, i64 val);
	auto get_reg(usz reg) -> i64;

private:
	std::array<i64, 32> registers { };
	csr_state csr;
	u64 pc { 0 };
};

}
