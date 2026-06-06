#pragma once

#include <array>
#include <cstdint>

namespace riscy_emu {

struct cpu_state {
	std::array<int64_t, 32> registers { };
	uint64_t pc { 0 };

private:
	auto set_reg(size_t reg, int64_t val);

	auto get_reg(size_t reg) -> int64_t;
};

}
