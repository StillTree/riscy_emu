#pragma once

#include <cstdlib>
#include <typedefs.hpp>
#include <variant>

namespace riscy_emu {

struct encoding_s {
	u8 rs1;
	u8 rs2;
	i64 imm;

	explicit encoding_s(u32 inst);
};

struct encoding_b {
	u8 rs1;
	u8 rs2;
	i64 imm;

	explicit encoding_b(u32 inst);
};

struct encoding_j {
	u8 rd;
	i64 imm;

	explicit encoding_j(u32 inst);
};

struct encoding_i {
	u8 rd;
	u8 rs1;
	i64 imm;

	explicit encoding_i(u32 inst);
};

struct encoding_i_shifts {
	u8 rd;
	u8 rs1;
	u8 shamt;
	i64 imm;

	explicit encoding_i_shifts(u32 inst);
};

struct encoding_u {
	u8 rd;
	i64 imm;

	explicit encoding_u(u32 inst);
};

struct encoding_r {
	u8 rd;
	u8 rs1;
	u8 rs2;

	explicit encoding_r(u32 inst);
};

enum class op : u8 {
	addi,
	slti,
	sltiu,
	xori,
	ori,
	andi,
	slli,
	srai,
	srli,
	addiw,
	slliw,
	sraiw,
	srliw,
	lui,
	auipc,
	add,
	sub,
	slt,
	sltu,
	xor_,
	or_,
	and_,
	sll,
	srl,
	sra,
	addw,
	subw,
	sllw,
	srlw,
	sraw,
	jal,
	jalr,
	beq,
	bne,
	blt,
	bge,
	bltu,
	bgeu,
	lb,
	lbu,
	lh,
	lhu,
	lw,
	lwu,
	ld,
	sb,
	sh,
	sw,
	sd,
	fence,
	ecall,
	ebreak,
	mret,
	csrrw,
	csrrs,
	csrrc,
	csrrwi,
	csrrsi,
	csrrci,
};

using inst_data = std::variant<encoding_s, encoding_b, encoding_j, encoding_i, encoding_i_shifts, encoding_u, encoding_r>;

struct inst {
	op op;
	inst_data data;
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

auto decode(u32 raw) -> inst;

}
