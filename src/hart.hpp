#pragma once

#include "csr.hpp"
#include "mem_bus.hpp"
#include "trap.hpp"
#include "typedefs.hpp"

#include <array>
#include <gsl/gsl>

namespace riscy_emu {

class hart_state {
public:
	hart_state() = delete;
	explicit hart_state(mem_bus* bus);

	auto step() -> void;

private:
	auto set_reg(usz reg, i64 val) -> void;
	auto get_reg(usz reg) -> i64;

	auto handle_trap(trap_cause cause) -> void;

	std::array<i64, 32> registers { };
	csr_state csr;
	u64 pc { 0 };
	gsl::not_null<mem_bus*> bus;
};

}
