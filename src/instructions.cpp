#include "instructions.hpp"

namespace riscy_emu {

encoding_s::encoding_s(u32 inst)
	: rs1(static_cast<u8>((inst >> 15) & 0x1F))
	, rs2(static_cast<u8>((inst >> 20) & 0x1F))
{
	u32 bits_11_5 = (inst >> 25) & 0x7F;
	u32 bits_4_0 = (inst >> 7) & 0x1F;
	u32 res = (bits_11_5 << 5) | bits_4_0;

	imm = (static_cast<i64>(res) << 52) >> 52;
}

encoding_b::encoding_b(u32 inst)
	: rs1(static_cast<u8>((inst >> 15) & 0x1F))
	, rs2(static_cast<u8>((inst >> 20) & 0x1F))
{
	u32 bit_12 = (inst >> 31) & 0x1;
	u32 bit_11 = (inst >> 7) & 0x1;
	u32 bits_10_5 = (inst >> 25) & 0x3F;
	u32 bits_4_1 = (inst >> 8) & 0xF;

	u32 res = (bit_12 << 12) | (bit_11 << 11) | (bits_10_5 << 5) | (bits_4_1 << 1);

	imm = (static_cast<i64>(res) << 51) >> 51;
}

encoding_j::encoding_j(u32 inst)
	: rd(static_cast<u8>((inst >> 7) & 0x1f))
{
	u32 bit_20 = (inst >> 31) & 0x1;
	u32 bits_10_1 = (inst >> 21) & 0x3ff;
	u32 bit_11 = (inst >> 20) & 0x1;
	u32 bits_19_12 = (inst >> 12) & 0xff;

	u32 res = (bit_20 << 20) | (bits_19_12 << 12) | (bit_11 << 11) | (bits_10_1 << 1);

	imm = (static_cast<i64>(res) << 43) >> 43;
}

encoding_i::encoding_i(u32 inst)
	: rd(static_cast<u8>((inst >> 7) & 0x1F))
	, rs1(static_cast<u8>((inst >> 15) & 0x1F))
	, imm(static_cast<i32>(inst) >> 20)
{
}

encoding_i_shifts::encoding_i_shifts(u32 inst)
	: rd(static_cast<u8>((inst >> 7) & 0x1f))
	, rs1(static_cast<u8>((inst >> 15) & 0x1f))
	, shamt(static_cast<u8>((inst >> 20) & 0x3f))
	, imm(static_cast<i64>(static_cast<i32>(inst) >> 26))
{
}

encoding_u::encoding_u(u32 inst)
	: rd(static_cast<u8>((inst >> 7) & 0x1f))
	, imm(static_cast<i64>(static_cast<i32>(inst) & ~0xfff))
{
}

encoding_r::encoding_r(u32 inst)
	: rd(static_cast<u8>((inst >> 7) & 0x1f))
	, rs1(static_cast<u8>((inst >> 15) & 0x1f))
	, rs2(static_cast<u8>((inst >> 20) & 0x1f))
{
}

auto decode(u32 raw) -> inst
{
	u8 opcode = static_cast<u8>(raw & 0x7f);

	u8 funct3 = static_cast<u8>((raw >> 12) & 0x7);
	u8 funct7 = static_cast<u8>((raw >> 25) & 0x7f);

	switch (opcode) {
	case opcode::IMM:
		switch (funct3) {
		case 0b000:
			return inst { .op = op::addi, .data = inst_data { encoding_i(raw) } };
		case 0b010:
			return inst { .op = op::slti, .data = inst_data { encoding_i(raw) } };
		case 0b011:
			return inst { .op = op::sltiu, .data = inst_data { encoding_i(raw) } };
		case 0b100:
			return inst { .op = op::xori, .data = inst_data { encoding_i(raw) } };
		case 0b110:
			return inst { .op = op::ori, .data = inst_data { encoding_i(raw) } };
		case 0b111:
			return inst { .op = op::andi, .data = inst_data { encoding_i(raw) } };
		case 0b001:
			return inst { .op = op::slli, .data = inst_data { encoding_i_shifts(raw) } };
		case 0b101: {
			encoding_i_shifts enc(raw);

			if (enc.imm == 0x10) {
				return inst { .op = op::srai, .data = inst_data { enc } };
			}

			return inst { .op = op::srli, .data = inst_data { enc } };
		}
		default:
			std::abort();
		};
		break;
	case opcode::IMM32:
		switch (funct3) {
		case 0b000:
			return inst { .op = op::addiw, .data = inst_data { encoding_i(raw) } };
		case 0b001:
			return inst { .op = op::slliw, .data = inst_data { encoding_i_shifts(raw) } };
		case 0b101: {
			encoding_i_shifts enc(raw);

			if (enc.imm == 0x10) {
				return inst { .op = op::sraiw, .data = inst_data { enc } };
			}

			return inst { .op = op::srliw, .data = inst_data { enc } };
		}
		default:
			std::abort();
		};
		break;
	case opcode::LUI:
		return inst { .op = op::lui, .data = inst_data { encoding_u(raw) } };
	case opcode::AUIPC:
		return inst { .op = op::auipc, .data = inst_data { encoding_u(raw) } };
	case opcode::OP:
		switch (funct3) {
		case 0b000:
			if (funct7 == 0x0) {
				return inst { .op = op::add, .data = inst_data { encoding_r(raw) } };
			} else if (funct7 == 0x20) {
				return inst { .op = op::sub, .data = inst_data { encoding_r(raw) } };
			} else {
				std::abort();
			}
		case 0b010:
			return inst { .op = op::slt, .data = inst_data { encoding_r(raw) } };
		case 0b011:
			return inst { .op = op::sltu, .data = inst_data { encoding_r(raw) } };
		case 0b100:
			return inst { .op = op::xor_, .data = inst_data { encoding_r(raw) } };
		case 0b110:
			return inst { .op = op::or_, .data = inst_data { encoding_r(raw) } };
		case 0b111:
			return inst { .op = op::and_, .data = inst_data { encoding_r(raw) } };
		case 0b001:
			return inst { .op = op::sll, .data = inst_data { encoding_r(raw) } };
		case 0b101:
			if (funct7 == 0x0) {
				return inst { .op = op::srl, .data = inst_data { encoding_r(raw) } };
			} else if (funct7 == 0x20) {
				return inst { .op = op::sra, .data = inst_data { encoding_r(raw) } };
			} else {
				std::abort();
			}
		default:
			std::abort();
		};
	case opcode::OP32:
		switch (funct3) {
		case 0b000:
			if (funct7 == 0x0) {
				return inst { .op = op::addw, .data = inst_data { encoding_r(raw) } };
			} else if (funct7 == 0x20) {
				return inst { .op = op::subw, .data = inst_data { encoding_r(raw) } };
			} else {
				std::abort();
			}
		case 0b001:
			return inst { .op = op::sllw, .data = inst_data { encoding_r(raw) } };
		case 0b101:
			if (funct7 == 0x0) {
				return inst { .op = op::srlw, .data = inst_data { encoding_r(raw) } };
			} else if (funct7 == 0x20) {
				return inst { .op = op::sraw, .data = inst_data { encoding_r(raw) } };
			} else {
				std::abort();
			}
		default:
			std::abort();
		};
	case opcode::JAL:
		return inst { .op = op::jal, .data = inst_data { encoding_j(raw) } };
	case opcode::JALR:
		return inst { .op = op::jalr, .data = inst_data { encoding_i(raw) } };
	case opcode::BRANCH:
		switch (funct3) {
		case 0b000:
			return inst { .op = op::beq, .data = inst_data { encoding_b(raw) } };
		case 0b001:
			return inst { .op = op::bne, .data = inst_data { encoding_b(raw) } };
		case 0b100:
			return inst { .op = op::blt, .data = inst_data { encoding_b(raw) } };
		case 0b101:
			return inst { .op = op::bge, .data = inst_data { encoding_b(raw) } };
		case 0b110:
			return inst { .op = op::bltu, .data = inst_data { encoding_b(raw) } };
		case 0b111:
			return inst { .op = op::bgeu, .data = inst_data { encoding_b(raw) } };
		default:
			std::abort();
		};
	case opcode::LOAD:
		switch (funct3) {
		case 0b000:
			return inst { .op = op::lb, .data = inst_data { encoding_i(raw) } };
		case 0b100:
			return inst { .op = op::lbu, .data = inst_data { encoding_i(raw) } };
		case 0b001:
			return inst { .op = op::lh, .data = inst_data { encoding_i(raw) } };
		case 0b101:
			return inst { .op = op::lhu, .data = inst_data { encoding_i(raw) } };
		case 0b010:
			return inst { .op = op::lw, .data = inst_data { encoding_i(raw) } };
		case 0b110:
			return inst { .op = op::lwu, .data = inst_data { encoding_i(raw) } };
		case 0b011:
			return inst { .op = op::ld, .data = inst_data { encoding_i(raw) } };
		default:
			std::abort();
		};
	case opcode::STORE:
		switch (funct3) {
		case 0b000:
			return inst { .op = op::sb, .data = inst_data { encoding_s(raw) } };
		case 0b001:
			return inst { .op = op::sh, .data = inst_data { encoding_s(raw) } };
		case 0b010:
			return inst { .op = op::sw, .data = inst_data { encoding_s(raw) } };
		case 0b011:
			return inst { .op = op::sd, .data = inst_data { encoding_s(raw) } };
		default:
			std::abort();
		};
	case opcode::MISC_MEM:
		return inst { .op = op::fence, .data = inst_data { encoding_i(69) } };
	case opcode::SYSTEM:
		switch (funct3) {
		case 0b000: {
			encoding_i i(raw);

			switch (i.imm) {
			case 0b0000000000:
				return inst { .op = op::ecall, .data = inst_data { i } };
			case 0b0000000001:
				return inst { .op = op::ebreak, .data = inst_data { i } };
			case 0b1100000010:
				return inst { .op = op::mret, .data = inst_data { i } };
			default:
				std::abort();
			}
		}
		case 0b001:
			return inst { .op = op::csrrw, .data = inst_data { encoding_i(raw) } };
		case 0b010:
			return inst { .op = op::csrrs, .data = inst_data { encoding_i(raw) } };
		case 0b011:
			return inst { .op = op::csrrc, .data = inst_data { encoding_i(raw) } };
		case 0b101:
			return inst { .op = op::csrrwi, .data = inst_data { encoding_i(raw) } };
		case 0b110:
			return inst { .op = op::csrrsi, .data = inst_data { encoding_i(raw) } };
		case 0b111:
			return inst { .op = op::csrrci, .data = inst_data { encoding_i(raw) } };
		default:
			std::abort();
		};
	default:
		std::abort();
	}
}

}
