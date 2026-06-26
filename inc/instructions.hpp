#pragma once

#include "cpu.hpp"

namespace riscy_emu::inst {

using handler = void (*)(cpu_state& cpu_state, u32 raw);

// Base

auto addi(cpu_state& cpu_state, u32 raw) -> void;
auto slti(cpu_state& cpu_state, u32 raw) -> void;
auto sltiu(cpu_state& cpu_state, u32 raw) -> void;
auto xori(cpu_state& cpu_state, u32 raw) -> void;
auto ori(cpu_state& cpu_state, u32 raw) -> void;
auto andi(cpu_state& cpu_state, u32 raw) -> void;
auto slli(cpu_state& cpu_state, u32 raw) -> void;
auto srai(cpu_state& cpu_state, u32 raw) -> void;
auto srli(cpu_state& cpu_state, u32 raw) -> void;
auto addiw(cpu_state& cpu_state, u32 raw) -> void;
auto slliw(cpu_state& cpu_state, u32 raw) -> void;
auto sraiw(cpu_state& cpu_state, u32 raw) -> void;
auto srliw(cpu_state& cpu_state, u32 raw) -> void;
auto lui(cpu_state& cpu_state, u32 raw) -> void;
auto auipc(cpu_state& cpu_state, u32 raw) -> void;
auto add(cpu_state& cpu_state, u32 raw) -> void;
auto sub(cpu_state& cpu_state, u32 raw) -> void;
auto slt(cpu_state& cpu_state, u32 raw) -> void;
auto sltu(cpu_state& cpu_state, u32 raw) -> void;
auto xor_(cpu_state& cpu_state, u32 raw) -> void;
auto or_(cpu_state& cpu_state, u32 raw) -> void;
auto and_(cpu_state& cpu_state, u32 raw) -> void;
auto sll(cpu_state& cpu_state, u32 raw) -> void;
auto srl(cpu_state& cpu_state, u32 raw) -> void;
auto sra(cpu_state& cpu_state, u32 raw) -> void;
auto addw(cpu_state& cpu_state, u32 raw) -> void;
auto subw(cpu_state& cpu_state, u32 raw) -> void;
auto sllw(cpu_state& cpu_state, u32 raw) -> void;
auto srlw(cpu_state& cpu_state, u32 raw) -> void;
auto sraw(cpu_state& cpu_state, u32 raw) -> void;
auto jal(cpu_state& cpu_state, u32 raw) -> void;
auto jalr(cpu_state& cpu_state, u32 raw) -> void;
auto beq(cpu_state& cpu_state, u32 raw) -> void;
auto bne(cpu_state& cpu_state, u32 raw) -> void;
auto blt(cpu_state& cpu_state, u32 raw) -> void;
auto bge(cpu_state& cpu_state, u32 raw) -> void;
auto bltu(cpu_state& cpu_state, u32 raw) -> void;
auto bgeu(cpu_state& cpu_state, u32 raw) -> void;
auto lb(cpu_state& cpu_state, u32 raw) -> void;
auto lbu(cpu_state& cpu_state, u32 raw) -> void;
auto lh(cpu_state& cpu_state, u32 raw) -> void;
auto lhu(cpu_state& cpu_state, u32 raw) -> void;
auto lw(cpu_state& cpu_state, u32 raw) -> void;
auto lwu(cpu_state& cpu_state, u32 raw) -> void;
auto ld(cpu_state& cpu_state, u32 raw) -> void;
auto sb(cpu_state& cpu_state, u32 raw) -> void;
auto sh(cpu_state& cpu_state, u32 raw) -> void;
auto sw(cpu_state& cpu_state, u32 raw) -> void;
auto sd(cpu_state& cpu_state, u32 raw) -> void;
auto fence(cpu_state& cpu_state, u32 raw) -> void;
auto ecall(cpu_state& cpu_state, u32 raw) -> void;
auto ebreak(cpu_state& cpu_state, u32 raw) -> void;
auto mret(cpu_state& cpu_state, u32 raw) -> void;

// Zicsr

auto csrrw(cpu_state& cpu_state, u32 raw) -> void;
auto csrrs(cpu_state& cpu_state, u32 raw) -> void;
auto csrrc(cpu_state& cpu_state, u32 raw) -> void;
auto csrrwi(cpu_state& cpu_state, u32 raw) -> void;
auto csrrsi(cpu_state& cpu_state, u32 raw) -> void;
auto csrrci(cpu_state& cpu_state, u32 raw) -> void;

}
