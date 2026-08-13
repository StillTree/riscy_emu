#pragma once

#include "typedefs.hpp"

#include <cstdlib>

namespace riscy_emu {

struct mstatus {
	static constexpr usz MIE_SHIFT = 3;
	static constexpr usz MPIE_SHIFT = 7;
	static constexpr usz MPP_SHIFT = 11;

	static constexpr u64 M_WRITE_MASK = (1 << MIE_SHIFT) | (1 << MPIE_SHIFT) | (3 << MPP_SHIFT);
	static constexpr u64 M_READ_MASK = M_WRITE_MASK;

	[[nodiscard]] auto mie() const -> bool;
	auto mie(bool val) -> void;

	[[nodiscard]] auto mpie() const -> bool;
	auto mpie(bool val) -> void;

	[[nodiscard]] auto mpp() const -> u8;
	auto mpp(u8 val) -> void;

	auto write_m(u64 val) -> void;
	[[nodiscard]] auto read_m() const -> u64;

private:
	u64 bits { 0 };
};

namespace csr::addr {

	constexpr u16 MSTATUS = 0x300;
	constexpr u16 MTVEC = 0x305;
	constexpr u16 MEPC = 0x341;
	constexpr u16 MCAUSE = 0x342;
	constexpr u16 MTVAL = 0x343;
	constexpr u16 MTVAL2 = 0x34b;
	constexpr u16 MISA = 0x301;
	constexpr u16 MVENDORID = 0xf11;
	constexpr u16 MHARTID = 0xf14;
	constexpr u16 MNSTATUS = 0x744;
	constexpr u16 PMPCFG0 = 0x3a0;
	constexpr u16 PMPADDR0 = 0x3b0;
	constexpr u16 MIE = 0x304;
	constexpr u16 SATP = 0x180;
	constexpr u16 MEDELEG = 0x302;
	constexpr u16 MIDELEG = 0x303;

}

struct csr_state {
	auto write(u16 addr, u64 val) -> void;
	[[nodiscard]] auto read(u16 addr) const -> u64;

private:
	struct mstatus mstatus { };
	u64 mcause { 0 };
	u64 mepc { 0 };
	u64 mtvec { 0 };
	u64 mnstatus { 0 };
};

}
