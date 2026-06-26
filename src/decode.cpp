#include "decode.hpp"

namespace riscy_emu {

namespace {

	auto decode_imm(u8 funct3, u32 raw) -> inst::handler
	{
		switch (funct3) {
		case 0b000:
			return inst::addi;
		case 0b010:
			return inst::slti;
		case 0b011:
			return inst::sltiu;
		case 0b100:
			return inst::xori;
		case 0b110:
			return inst::ori;
		case 0b111:
			return inst::andi;
		case 0b001:
			return inst::slli;
		case 0b101: {
			encoding_i_shifts enc { raw };

			if (enc.imm() == 0x10) {
				return inst::srai;
			}

			return inst::srli;
		}
		default:
			std::abort();
		};
	}

	auto decode_imm32(u8 funct3, u32 raw) -> inst::handler
	{
		switch (funct3) {
		case 0b000:
			return inst::addiw;
		case 0b001:
			return inst::slliw;
		case 0b101: {
			encoding_i_shifts enc { raw };

			if (enc.imm() == 0x10) {
				return inst::sraiw;
			}

			return inst::srliw;
		}
		default:
			std::abort();
		};
	}

	auto decode_op(u8 funct3, u8 funct7) -> inst::handler
	{
		switch (funct3) {
		case 0b000:
			if (funct7 == 0x0) {
				return inst::add;
			} else if (funct7 == 0x20) {
				return inst::sub;
			} else {
				std::abort();
			}
		case 0b010:
			return inst::slt;
		case 0b011:
			return inst::sltu;
		case 0b100:
			return inst::xor_;
		case 0b110:
			return inst::or_;
		case 0b111:
			return inst::and_;
		case 0b001:
			return inst::sll;
		case 0b101:
			if (funct7 == 0x0) {
				return inst::srl;
			} else if (funct7 == 0x20) {
				return inst::sra;
			} else {
				std::abort();
			}
		default:
			std::abort();
		};
	}

	auto decode_op32(u8 funct3, u8 funct7) -> inst::handler
	{
		switch (funct3) {
		case 0b000:
			if (funct7 == 0x0) {
				return inst::addw;
			} else if (funct7 == 0x20) {
				return inst::subw;
			} else {
				std::abort();
			}
		case 0b001:
			return inst::sllw;
		case 0b101:
			if (funct7 == 0x0) {
				return inst::srlw;
			} else if (funct7 == 0x20) {
				return inst::sraw;
			} else {
				std::abort();
			}
		default:
			std::abort();
		};
	}

	auto decode_branch(u8 funct3) -> inst::handler
	{
		switch (funct3) {
		case 0b000:
			return inst::beq;
		case 0b001:
			return inst::bne;
		case 0b100:
			return inst::blt;
		case 0b101:
			return inst::bge;
		case 0b110:
			return inst::bltu;
		case 0b111:
			return inst::bgeu;
		default:
			std::abort();
		};
	}

	auto decode_load(u8 funct3) -> inst::handler
	{
		switch (funct3) {
		case 0b000:
			return inst::lb;
		case 0b100:
			return inst::lbu;
		case 0b001:
			return inst::lh;
		case 0b101:
			return inst::lhu;
		case 0b010:
			return inst::lw;
		case 0b110:
			return inst::lwu;
		case 0b011:
			return inst::ld;
		default:
			std::abort();
		};
	}

	auto decode_store(u8 funct3) -> inst::handler
	{
		switch (funct3) {
		case 0b000:
			return inst::sb;
		case 0b001:
			return inst::sh;
		case 0b010:
			return inst::sw;
		case 0b011:
			return inst::sd;
		default:
			std::abort();
		};
	}

	auto decode_system(u8 funct3, u32 raw) -> inst::handler
	{
		switch (funct3) {
		case 0b000: {
			encoding_i enc { raw };

			switch (enc.imm()) {
			case 0b0000000000:
				return inst::ecall;
			case 0b0000000001:
				return inst::ebreak;
			case 0b1100000010:
				return inst::mret;
			default:
				std::abort();
			}
		}
		case 0b001:
			return inst::csrrw;
		case 0b010:
			return inst::csrrs;
		case 0b011:
			return inst::csrrc;
		case 0b101:
			return inst::csrrwi;
		case 0b110:
			return inst::csrrsi;
		case 0b111:
			return inst::csrrci;
		default:
			std::abort();
		};
	}

}

auto decode(u32 raw) -> inst::handler
{
	u8 opcode = static_cast<u8>(raw & 0x7f);

	u8 funct3 = static_cast<u8>((raw >> 12) & 0x7);
	u8 funct7 = static_cast<u8>((raw >> 25) & 0x7f);

	// TODO: Change this into jump tables or something faster
	switch (opcode) {
	case opcode::IMM:
		return decode_imm(funct3, raw);
	case opcode::IMM32:
		return decode_imm32(funct3, raw);
	case opcode::LUI:
		return inst::lui;
	case opcode::AUIPC:
		return inst::auipc;
	case opcode::OP:
		return decode_op(funct3, funct7);
	case opcode::OP32:
		return decode_op32(funct3, funct7);
	case opcode::JAL:
		return inst::jal;
	case opcode::JALR:
		return inst::jalr;
	case opcode::BRANCH:
		return decode_branch(funct3);
	case opcode::LOAD:
		return decode_load(funct3);
	case opcode::STORE:
		return decode_store(funct3);
	case opcode::MISC_MEM:
		return inst::fence;
	case opcode::SYSTEM:
		return decode_system(funct3, raw);
	default:
		std::abort();
	}
}

}
