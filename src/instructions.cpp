#include "instructions.hpp"

#include "decode.hpp"

namespace riscy_emu::inst {

auto addi(cpu_state& cpu_state, u32 raw) -> void
{
	auto enc = encoding_i { raw };
}

auto slti(cpu_state& cpu_state, u32 raw) -> void
{
	auto enc = encoding_i { raw };
}

auto sltiu(cpu_state& cpu_state, u32 raw) -> void
{
	auto enc = encoding_i { raw };
}

}
