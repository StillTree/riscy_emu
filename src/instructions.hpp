#pragma once

#include "hart.hpp"

namespace riscy_emu::inst {

using handler = void (*)(hart_state& cpu_state, u32 raw);

// Base

auto addi(hart_state& cpu_state, u32 raw) -> void;
auto slti(hart_state& cpu_state, u32 raw) -> void;
auto sltiu(hart_state& cpu_state, u32 raw) -> void;
auto xori(hart_state& cpu_state, u32 raw) -> void;
auto ori(hart_state& cpu_state, u32 raw) -> void;
auto andi(hart_state& cpu_state, u32 raw) -> void;
auto slli(hart_state& cpu_state, u32 raw) -> void;
auto srai(hart_state& cpu_state, u32 raw) -> void;
auto srli(hart_state& cpu_state, u32 raw) -> void;
auto addiw(hart_state& cpu_state, u32 raw) -> void;
auto slliw(hart_state& cpu_state, u32 raw) -> void;
auto sraiw(hart_state& cpu_state, u32 raw) -> void;
auto srliw(hart_state& cpu_state, u32 raw) -> void;
auto lui(hart_state& cpu_state, u32 raw) -> void;
auto auipc(hart_state& cpu_state, u32 raw) -> void;
auto add(hart_state& cpu_state, u32 raw) -> void;
auto sub(hart_state& cpu_state, u32 raw) -> void;
auto slt(hart_state& cpu_state, u32 raw) -> void;
auto sltu(hart_state& cpu_state, u32 raw) -> void;
auto xor_(hart_state& cpu_state, u32 raw) -> void;
auto or_(hart_state& cpu_state, u32 raw) -> void;
auto and_(hart_state& cpu_state, u32 raw) -> void;
auto sll(hart_state& cpu_state, u32 raw) -> void;
auto srl(hart_state& cpu_state, u32 raw) -> void;
auto sra(hart_state& cpu_state, u32 raw) -> void;
auto addw(hart_state& cpu_state, u32 raw) -> void;
auto subw(hart_state& cpu_state, u32 raw) -> void;
auto sllw(hart_state& cpu_state, u32 raw) -> void;
auto srlw(hart_state& cpu_state, u32 raw) -> void;
auto sraw(hart_state& cpu_state, u32 raw) -> void;
auto jal(hart_state& cpu_state, u32 raw) -> void;
auto jalr(hart_state& cpu_state, u32 raw) -> void;
auto beq(hart_state& cpu_state, u32 raw) -> void;
auto bne(hart_state& cpu_state, u32 raw) -> void;
auto blt(hart_state& cpu_state, u32 raw) -> void;
auto bge(hart_state& cpu_state, u32 raw) -> void;
auto bltu(hart_state& cpu_state, u32 raw) -> void;
auto bgeu(hart_state& cpu_state, u32 raw) -> void;
auto lb(hart_state& cpu_state, u32 raw) -> void;
auto lbu(hart_state& cpu_state, u32 raw) -> void;
auto lh(hart_state& cpu_state, u32 raw) -> void;
auto lhu(hart_state& cpu_state, u32 raw) -> void;
auto lw(hart_state& cpu_state, u32 raw) -> void;
auto lwu(hart_state& cpu_state, u32 raw) -> void;
auto ld(hart_state& cpu_state, u32 raw) -> void;
auto sb(hart_state& cpu_state, u32 raw) -> void;
auto sh(hart_state& cpu_state, u32 raw) -> void;
auto sw(hart_state& cpu_state, u32 raw) -> void;
auto sd(hart_state& cpu_state, u32 raw) -> void;
auto fence(hart_state& cpu_state, u32 raw) -> void;
auto ecall(hart_state& cpu_state, u32 raw) -> void;
auto ebreak(hart_state& cpu_state, u32 raw) -> void;
auto mret(hart_state& cpu_state, u32 raw) -> void;

// Zicsr

auto csrrw(hart_state& cpu_state, u32 raw) -> void;
auto csrrs(hart_state& cpu_state, u32 raw) -> void;
auto csrrc(hart_state& cpu_state, u32 raw) -> void;
auto csrrwi(hart_state& cpu_state, u32 raw) -> void;
auto csrrsi(hart_state& cpu_state, u32 raw) -> void;
auto csrrci(hart_state& cpu_state, u32 raw) -> void;

}
