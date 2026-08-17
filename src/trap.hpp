#pragma once

#include "typedefs.hpp"

namespace riscy_emu {

enum class trap_cause : u8 {
	inst_addr_misalign = 0,
	inst_access_fault = 1,
	illegal_inst = 2,
	breakpoint = 3,
	load_addr_misalign = 4,
	load_access_fault = 5,
	store_amo_addr_misalign = 6,
	store_amo_access_fault = 7,
	ecall_from_user = 8,
	ecall_from_supervisor = 9,
	ecall_from_machine = 11,
	inst_page_fault = 12,
	load_page_fault = 13,
	store_amo_page_fault = 15,
	double_trap = 16,
	software_check = 18,
	hardware_error = 19,
};

}
