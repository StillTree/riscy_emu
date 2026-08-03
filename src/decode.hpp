#pragma once

#include "instructions.hpp"
#include "typedefs.hpp"

#include <cstdlib>

namespace riscy_emu {

struct encoding_s {
	explicit encoding_s(u32 raw)
		: raw(raw)
	{
	}

	[[nodiscard]] constexpr auto rs1() const -> u8
	{
		return static_cast<u8>((raw >> 15) & 0x1F);
	}

	[[nodiscard]] constexpr auto rs2() const -> u8
	{
		return static_cast<u8>((raw >> 20) & 0x1F);
	}

	[[nodiscard]] constexpr auto imm() const -> i64
	{
		u32 bits_11_5 = (raw >> 25) & 0x7F;
		u32 bits_4_0 = (raw >> 7) & 0x1F;
		u32 res = (bits_11_5 << 5) | bits_4_0;

		return (static_cast<i64>(res) << 52) >> 52;
	}

private:
	u32 raw;
};

struct encoding_b {
	explicit encoding_b(u32 raw)
		: raw(raw)
	{
	}

	[[nodiscard]] constexpr auto rs1() const -> u8
	{
		return static_cast<u8>((raw >> 15) & 0x1F);
	}

	[[nodiscard]] constexpr auto rs2() const -> u8
	{
		return static_cast<u8>((raw >> 20) & 0x1F);
	}

	[[nodiscard]] constexpr auto imm() const -> i64
	{
		u32 bit_12 = (raw >> 31) & 0x1;
		u32 bit_11 = (raw >> 7) & 0x1;
		u32 bits_10_5 = (raw >> 25) & 0x3F;
		u32 bits_4_1 = (raw >> 8) & 0xF;

		u32 res = (bit_12 << 12) | (bit_11 << 11) | (bits_10_5 << 5) | (bits_4_1 << 1);

		return (static_cast<i64>(res) << 51) >> 51;
	}

private:
	u32 raw;
};

struct encoding_j {
	explicit encoding_j(u32 raw)
		: raw(raw)
	{
	}

	[[nodiscard]] constexpr auto rd() const -> u8
	{
		return static_cast<u8>((raw >> 7) & 0x1f);
	}

	[[nodiscard]] constexpr auto imm() const -> i64
	{
		u32 bit_20 = (raw >> 31) & 0x1;
		u32 bits_10_1 = (raw >> 21) & 0x3ff;
		u32 bit_11 = (raw >> 20) & 0x1;
		u32 bits_19_12 = (raw >> 12) & 0xff;

		u32 res = (bit_20 << 20) | (bits_19_12 << 12) | (bit_11 << 11) | (bits_10_1 << 1);

		return (static_cast<i64>(res) << 43) >> 43;
	}

private:
	u32 raw;
};

struct encoding_i {
	explicit encoding_i(u32 raw)
		: raw(raw)
	{
	}

	[[nodiscard]] constexpr auto rd() const -> u8
	{
		return static_cast<u8>((raw >> 7) & 0x1F);
	}

	[[nodiscard]] constexpr auto rs1() const -> u8
	{
		return static_cast<u8>((raw >> 15) & 0x1F);
	}

	[[nodiscard]] constexpr auto imm() const -> i64
	{
		return static_cast<i32>(raw) >> 20;
	}

private:
	u32 raw;
};

struct encoding_i_shifts {
	explicit encoding_i_shifts(u32 raw)
		: raw(raw)
	{
	}

	[[nodiscard]] constexpr auto rd() const -> u8
	{
		return static_cast<u8>((raw >> 7) & 0x1f);
	}

	[[nodiscard]] constexpr auto rs1() const -> u8
	{
		return static_cast<u8>((raw >> 15) & 0x1f);
	}

	[[nodiscard]] constexpr auto shamt() const -> u8
	{
		return static_cast<u8>((raw >> 20) & 0x3f);
	}

	[[nodiscard]] constexpr auto imm() const -> i64
	{
		return static_cast<i64>(static_cast<i32>(raw) >> 26);
	}

private:
	u32 raw;
};

struct encoding_u {
	explicit encoding_u(u32 raw)
		: raw(raw)
	{
	}

	[[nodiscard]] constexpr auto rd() const -> u8
	{
		return static_cast<u8>((raw >> 7) & 0x1f);
	}

	[[nodiscard]] constexpr auto imm() const -> i64
	{
		return static_cast<i64>(static_cast<i32>(raw) & ~0xfff);
	}

private:
	u32 raw;
};

struct encoding_r {
	explicit encoding_r(u32 raw)
		: raw(raw)
	{
	}

	[[nodiscard]] constexpr auto rd() const -> u8
	{
		return static_cast<u8>((raw >> 7) & 0x1f);
	}

	[[nodiscard]] constexpr auto rs1() const -> u8
	{
		return static_cast<u8>((raw >> 15) & 0x1f);
	}

	[[nodiscard]] constexpr auto rs2() const -> u8
	{
		return static_cast<u8>((raw >> 20) & 0x1f);
	}

private:
	u32 raw;
};

namespace opcode {

	constexpr u8 IMM = 0b0010011;
	constexpr u8 IMM32 = 0b0011011;
	constexpr u8 LUI = 0b0110111;
	constexpr u8 AUIPC = 0b0010111;
	constexpr u8 OP = 0b0110011;
	constexpr u8 OP32 = 0b0111011;
	constexpr u8 JAL = 0b1101111;
	constexpr u8 JALR = 0b1100111;
	constexpr u8 BRANCH = 0b1100011;
	constexpr u8 LOAD = 0b0000011;
	constexpr u8 STORE = 0b0100011;
	constexpr u8 MISC_MEM = 0b0001111;
	constexpr u8 SYSTEM = 0b1110011;

}

auto decode(u32 raw) -> inst::handler;

}
