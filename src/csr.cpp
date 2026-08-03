#include "csr.hpp"

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
	case csr::addr::SATP:
	case csr::addr::PMPADDR0:
	case csr::addr::PMPCFG0:
	case csr::addr::MIE:
	case csr::addr::MEDELEG:
	case csr::addr::MIDELEG:
		break;
	case csr::addr::MSTATUS:
		mstatus.write_m(val);
		break;
	case csr::addr::MTVEC:
		mtvec = val;
		break;
	case csr::addr::MCAUSE:
		mcause = val;
		break;
	case csr::addr::MEPC:
		mepc = val;
		break;
	case csr::addr::MNSTATUS:
		mnstatus = val;
		break;
	default:
		std::abort();
	}
}

auto csr_state::read(u16 addr) const -> u64
{
	switch (addr) {
	case csr::addr::MSTATUS:
		return mstatus.read_m();
	case csr::addr::MISA:
	case csr::addr::MHARTID:
	case csr::addr::SATP:
		return 0;
	case csr::addr::MTVEC:
		return mtvec;
	case csr::addr::MCAUSE:
		return mcause;
	case csr::addr::MEPC:
		return mepc;
	case csr::addr::MNSTATUS:
		return mnstatus;
	default:
		std::abort();
	}
}

}
