#include "csr.hpp"
#include <exception>

namespace riscy_emu {

auto mstatus::mie() const -> bool
{
	return (bits >> MIE_SHIFT) & 1;
}

auto mstatus::mie(bool val) -> void
{
	if (val) {
		bits |= 1 << MIE_SHIFT;
	} else {
		bits &= ~(1 << MIE_SHIFT);
	}
}

auto mstatus::mpie() const -> bool
{
	return (bits >> MPIE_SHIFT) & 1;
}

auto mstatus::mpie(bool val) -> void
{
	if (val) {
		bits |= 1 << MPIE_SHIFT;
	} else {
		bits &= ~(1 << MPIE_SHIFT);
	}
}

auto mstatus::mpp() const -> u8
{
	return (bits >> MPP_SHIFT) & 3;
}

auto mstatus::mpp(u8 val) -> void
{
	bits &= ~(3 << MPP_SHIFT);
	bits |= val << MPP_SHIFT;
}

auto mstatus::write_m(u64 val) -> void
{
	bits = (bits & ~M_WRITE_MASK) | (val & M_WRITE_MASK);
}

auto mstatus::read_m() const -> u64
{
	return bits & M_READ_MASK;
}

auto csr_state::write(u16 addr, u64 val) -> void
{
	switch (addr) {
		using namespace csr::addr;

	case SATP:
	case PMPADDR0:
	case PMPCFG0:
	case MIE:
	case MEDELEG:
	case MIDELEG:
		break;
	case MSTATUS:
		mstatus.write_m(val);
		break;
	case MTVEC:
		mtvec = val;
		break;
	case MCAUSE:
		mcause = val;
		break;
	case MEPC:
		mepc = val;
		break;
	case MNSTATUS:
		mnstatus = val;
		break;
	default:
		std::abort();
	}
}

auto csr_state::read(u16 addr) const -> u64
{
	switch (addr) {
		using namespace csr::addr;

	case MSTATUS:
		return mstatus.read_m();
	case MISA:
	case MHARTID:
	case SATP:
		return 0;
	case MTVEC:
		return mtvec;
	case MCAUSE:
		return mcause;
	case MEPC:
		return mepc;
	case MNSTATUS:
		return mnstatus;
	default:
		std::abort();
	}
}

auto csr_state::handle_trap(trap_cause cause, u64 cur_pc) -> u64
{
	auto mie = mstatus.mie();
	mstatus.mpie(mie);
	mstatus.mie(false);

	mcause = static_cast<u64>(cause);
	mepc = cur_pc;

	if ((mtvec & 3) != 0) {
		std::terminate();
	}

	return mtvec & ~3ULL;
}

}
