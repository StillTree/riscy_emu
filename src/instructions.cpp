#include "instructions.hpp"

#include "decode.hpp"

namespace riscy_emu::inst {

// Base

auto addi(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    i64 val = static_cast<i64>(static_cast<u64>(cpu_state.get_reg(inst.rs1())) + static_cast<u64>(inst.imm()));
    cpu_state.set_reg(inst.rd(), val);
}

auto slti(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    cpu_state.set_reg(inst.rd(), (cpu_state.get_reg(inst.rs1()) < inst.imm()) ? 1 : 0);
}

auto sltiu(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    cpu_state.set_reg(inst.rd(), (static_cast<u64>(cpu_state.get_reg(inst.rs1())) < static_cast<u64>(inst.imm())) ? 1 : 0);
}

auto xori(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    i64 val = cpu_state.get_reg(inst.rs1()) ^ inst.imm();
    cpu_state.set_reg(inst.rd(), val);
}

auto ori(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    i64 val = cpu_state.get_reg(inst.rs1()) | inst.imm();
    cpu_state.set_reg(inst.rd(), val);
}

auto andi(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    i64 val = cpu_state.get_reg(inst.rs1()) & inst.imm();
    cpu_state.set_reg(inst.rd(), val);
}

auto slli(hart_state& cpu_state, u32 raw) -> void {
    encoding_i_shifts inst(raw);
    i64 val = static_cast<i64>(static_cast<u64>(cpu_state.get_reg(inst.rs1())) << inst.shamt());
    cpu_state.set_reg(inst.rd(), val);
}

auto srli(hart_state& cpu_state, u32 raw) -> void {
    encoding_i_shifts inst(raw);
    u64 val = static_cast<u64>(cpu_state.get_reg(inst.rs1())) >> inst.shamt();
    cpu_state.set_reg(inst.rd(), static_cast<i64>(val));
}

auto srai(hart_state& cpu_state, u32 raw) -> void {
    encoding_i_shifts inst(raw);
    i64 val = cpu_state.get_reg(inst.rs1()) >> inst.shamt();
    cpu_state.set_reg(inst.rd(), val);
}

auto addiw(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    i32 val = static_cast<i32>(cpu_state.get_reg(inst.rs1())) + static_cast<i32>(inst.imm());
    cpu_state.set_reg(inst.rd(), static_cast<i64>(val));
}

auto slliw(hart_state& cpu_state, u32 raw) -> void {
    encoding_i_shifts inst(raw);
    i32 val = static_cast<i32>(static_cast<u32>(cpu_state.get_reg(inst.rs1())) << inst.shamt());
    cpu_state.set_reg(inst.rd(), static_cast<i64>(val));
}

auto srliw(hart_state& cpu_state, u32 raw) -> void {
    encoding_i_shifts inst(raw);
    i32 val = static_cast<i32>(static_cast<u32>(cpu_state.get_reg(inst.rs1())) >> inst.shamt());
    cpu_state.set_reg(inst.rd(), static_cast<i64>(val));
}

auto sraiw(hart_state& cpu_state, u32 raw) -> void {
    encoding_i_shifts inst(raw);
    i32 val = static_cast<i32>(cpu_state.get_reg(inst.rs1())) >> inst.shamt();
    cpu_state.set_reg(inst.rd(), static_cast<i64>(val));
}

auto lui(hart_state& cpu_state, u32 raw) -> void {
    encoding_u inst(raw);
    cpu_state.set_reg(inst.rd(), inst.imm());
}

auto auipc(hart_state& cpu_state, u32 raw) -> void {
    encoding_u inst(raw);
    i64 val = inst.imm() + static_cast<i64>(cpu_state.pc);
    cpu_state.set_reg(inst.rd(), val);
}

auto add(hart_state& cpu_state, u32 raw) -> void {
    encoding_r inst(raw);
    i64 val = static_cast<i64>(static_cast<u64>(cpu_state.get_reg(inst.rs1())) + static_cast<u64>(cpu_state.get_reg(inst.rs2())));
    cpu_state.set_reg(inst.rd(), val);
}

auto sub(hart_state& cpu_state, u32 raw) -> void {
    encoding_r inst(raw);
    i64 val = static_cast<i64>(static_cast<u64>(cpu_state.get_reg(inst.rs1())) - static_cast<u64>(cpu_state.get_reg(inst.rs2())));
    cpu_state.set_reg(inst.rd(), val);
}

auto slt(hart_state& cpu_state, u32 raw) -> void {
    encoding_r inst(raw);
    cpu_state.set_reg(inst.rd(), (cpu_state.get_reg(inst.rs1()) < cpu_state.get_reg(inst.rs2())) ? 1 : 0);
}

auto sltu(hart_state& cpu_state, u32 raw) -> void {
    encoding_r inst(raw);
    cpu_state.set_reg(inst.rd(), (static_cast<u64>(cpu_state.get_reg(inst.rs1())) < static_cast<u64>(cpu_state.get_reg(inst.rs2()))) ? 1 : 0);
}

auto xor_(hart_state& cpu_state, u32 raw) -> void {
    encoding_r inst(raw);
    i64 val = cpu_state.get_reg(inst.rs1()) ^ cpu_state.get_reg(inst.rs2());
    cpu_state.set_reg(inst.rd(), val);
}

auto or_(hart_state& cpu_state, u32 raw) -> void {
    encoding_r inst(raw);
    i64 val = cpu_state.get_reg(inst.rs1()) | cpu_state.get_reg(inst.rs2());
    cpu_state.set_reg(inst.rd(), val);
}

auto and_(hart_state& cpu_state, u32 raw) -> void {
    encoding_r inst(raw);
    i64 val = cpu_state.get_reg(inst.rs1()) & cpu_state.get_reg(inst.rs2());
    cpu_state.set_reg(inst.rd(), val);
}

auto sll(hart_state& cpu_state, u32 raw) -> void {
    encoding_r inst(raw);
    i64 val = static_cast<i64>(static_cast<u64>(cpu_state.get_reg(inst.rs1())) << static_cast<u32>(cpu_state.get_reg(inst.rs2())));
    cpu_state.set_reg(inst.rd(), val);
}

auto srl(hart_state& cpu_state, u32 raw) -> void {
    encoding_r inst(raw);
    u64 val = static_cast<u64>(cpu_state.get_reg(inst.rs1())) >> static_cast<u32>(cpu_state.get_reg(inst.rs2()));
    cpu_state.set_reg(inst.rd(), static_cast<i64>(val));
}

auto sra(hart_state& cpu_state, u32 raw) -> void {
    encoding_r inst(raw);
    i64 val = cpu_state.get_reg(inst.rs1()) >> static_cast<u32>(cpu_state.get_reg(inst.rs2()));
    cpu_state.set_reg(inst.rd(), val);
}

auto addw(hart_state& cpu_state, u32 raw) -> void {
    encoding_r inst(raw);
    i32 val = static_cast<i32>(cpu_state.get_reg(inst.rs1())) + static_cast<i32>(cpu_state.get_reg(inst.rs2()));
    cpu_state.set_reg(inst.rd(), static_cast<i64>(val));
}

auto subw(hart_state& cpu_state, u32 raw) -> void {
    encoding_r inst(raw);
    i32 val = static_cast<i32>(cpu_state.get_reg(inst.rs1())) - static_cast<i32>(cpu_state.get_reg(inst.rs2()));
    cpu_state.set_reg(inst.rd(), static_cast<i64>(val));
}

auto sllw(hart_state& cpu_state, u32 raw) -> void {
    encoding_r inst(raw);
    i32 val = static_cast<i32>(static_cast<u32>(cpu_state.get_reg(inst.rs1())) << static_cast<u32>(cpu_state.get_reg(inst.rs2())));
    cpu_state.set_reg(inst.rd(), static_cast<i64>(val));
}

auto srlw(hart_state& cpu_state, u32 raw) -> void {
    encoding_r inst(raw);
    i32 val = static_cast<i32>(static_cast<u32>(cpu_state.get_reg(inst.rs1())) >> static_cast<u32>(cpu_state.get_reg(inst.rs2())));
    cpu_state.set_reg(inst.rd(), static_cast<i64>(val));
}

auto sraw(hart_state& cpu_state, u32 raw) -> void {
    encoding_r inst(raw);
    i32 val = static_cast<i32>(cpu_state.get_reg(inst.rs1())) >> static_cast<u32>(cpu_state.get_reg(inst.rs2()));
    cpu_state.set_reg(inst.rd(), static_cast<i64>(val));
}

auto jal(hart_state& cpu_state, u32 raw) -> void {
    encoding_j inst(raw);
    u64 target = cpu_state.pc + static_cast<u64>(inst.imm());
    cpu_state.set_reg(inst.rd(), static_cast<i64>(cpu_state.pc + 4));
    cpu_state.pc = target;
}

auto jalr(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    u64 target = (static_cast<u64>(cpu_state.get_reg(inst.rs1()) + inst.imm())) & ~1ULL;
    cpu_state.set_reg(inst.rd(), static_cast<i64>(cpu_state.pc + 4));
    cpu_state.pc = target;
}

auto beq(hart_state& cpu_state, u32 raw) -> void {
    encoding_b inst(raw);
    u64 target = cpu_state.pc + static_cast<u64>(inst.imm());
    if (cpu_state.get_reg(inst.rs1()) == cpu_state.get_reg(inst.rs2())) {
        cpu_state.pc = target;
    }
}

auto bne(hart_state& cpu_state, u32 raw) -> void {
    encoding_b inst(raw);
    u64 target = cpu_state.pc + static_cast<u64>(inst.imm());
    if (cpu_state.get_reg(inst.rs1()) != cpu_state.get_reg(inst.rs2())) {
        cpu_state.pc = target;
    }
}

auto blt(hart_state& cpu_state, u32 raw) -> void {
    encoding_b inst(raw);
    u64 target = cpu_state.pc + static_cast<u64>(inst.imm());
    if (cpu_state.get_reg(inst.rs1()) < cpu_state.get_reg(inst.rs2())) {
        cpu_state.pc = target;
    }
}

auto bge(hart_state& cpu_state, u32 raw) -> void {
    encoding_b inst(raw);
    u64 target = cpu_state.pc + static_cast<u64>(inst.imm());
    if (cpu_state.get_reg(inst.rs1()) >= cpu_state.get_reg(inst.rs2())) {
        cpu_state.pc = target;
    }
}

auto bltu(hart_state& cpu_state, u32 raw) -> void {
    encoding_b inst(raw);
    u64 target = cpu_state.pc + static_cast<u64>(inst.imm());
    if (static_cast<u64>(cpu_state.get_reg(inst.rs1())) < static_cast<u64>(cpu_state.get_reg(inst.rs2()))) {
        cpu_state.pc = target;
    }
}

auto bgeu(hart_state& cpu_state, u32 raw) -> void {
    encoding_b inst(raw);
    u64 target = cpu_state.pc + static_cast<u64>(inst.imm());
    if (static_cast<u64>(cpu_state.get_reg(inst.rs1())) >= static_cast<u64>(cpu_state.get_reg(inst.rs2()))) {
        cpu_state.pc = target;
    }
}

auto lb(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    u64 addr = static_cast<u64>(cpu_state.get_reg(inst.rs1()) + inst.imm());
    i8 val = static_cast<i8>(cpu_state.bus.read<u8>(addr).value());
    cpu_state.set_reg(inst.rd(), static_cast<i64>(val));
}

auto lbu(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    u64 addr = static_cast<u64>(cpu_state.get_reg(inst.rs1()) + inst.imm());
    u64 val = cpu_state.bus.read<u8>(addr).value();
    cpu_state.set_reg(inst.rd(), static_cast<i64>(val));
}

auto lh(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    u64 addr = static_cast<u64>(cpu_state.get_reg(inst.rs1()) + inst.imm());
    i16 val = static_cast<i16>(cpu_state.bus.read<u16>(addr).value());
    cpu_state.set_reg(inst.rd(), static_cast<i64>(val));
}

auto lhu(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    u64 addr = static_cast<u64>(cpu_state.get_reg(inst.rs1()) + inst.imm());
    u64 val = cpu_state.bus.read<u16>(addr).value();
    cpu_state.set_reg(inst.rd(), static_cast<i64>(val));
}

auto lw(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    u64 addr = static_cast<u64>(cpu_state.get_reg(inst.rs1()) + inst.imm());
    i32 val = static_cast<i32>(cpu_state.bus.read<u32>(addr).value());
    cpu_state.set_reg(inst.rd(), static_cast<i64>(val));
}

auto lwu(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    u64 addr = static_cast<u64>(cpu_state.get_reg(inst.rs1()) + inst.imm());
    u64 val = cpu_state.bus.read<u32>(addr).value();
    cpu_state.set_reg(inst.rd(), static_cast<i64>(val));
}

auto ld(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    u64 addr = static_cast<u64>(cpu_state.get_reg(inst.rs1()) + inst.imm());
    i64 val = static_cast<i64>(cpu_state.bus.read<u64>(addr).value());
    cpu_state.set_reg(inst.rd(), val);
}

auto sb(hart_state& cpu_state, u32 raw) -> void {
    encoding_s inst(raw);
    u64 addr = static_cast<u64>(cpu_state.get_reg(inst.rs1()) + inst.imm());
    u8 val = static_cast<u8>(cpu_state.get_reg(inst.rs2()));
    (void)cpu_state.bus.write<u8>(addr, val);
}

auto sh(hart_state& cpu_state, u32 raw) -> void {
    encoding_s inst(raw);
    u64 addr = static_cast<u64>(cpu_state.get_reg(inst.rs1()) + inst.imm());
    u16 val = static_cast<u16>(cpu_state.get_reg(inst.rs2()));
    (void)cpu_state.bus.write<u16>(addr, val);
}

auto sw(hart_state& cpu_state, u32 raw) -> void {
    encoding_s inst(raw);
    u64 addr = static_cast<u64>(cpu_state.get_reg(inst.rs1()) + inst.imm());
    u32 val = static_cast<u32>(cpu_state.get_reg(inst.rs2()));
    (void)cpu_state.bus.write<u32>(addr, val);
}

auto sd(hart_state& cpu_state, u32 raw) -> void {
    encoding_s inst(raw);
    u64 addr = static_cast<u64>(cpu_state.get_reg(inst.rs1()) + inst.imm());
    u64 val = static_cast<u64>(cpu_state.get_reg(inst.rs2()));
    (void)cpu_state.bus.write<u64>(addr, val);
}

auto fence(hart_state& cpu_state, u32 raw) -> void {
    (void)cpu_state;
    (void)raw;
}

auto ecall(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    (void)inst;
    cpu_state.handle_trap(trap_cause::exception_ecall_from_machine);
}

auto ebreak(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    (void)inst;
    std::abort();
}

auto mret(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    (void)inst;
    cpu_state.handle_trap_exit();
}

// Zicsr

auto csrrw(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    u16 addr = static_cast<u16>(inst.imm()) & 0xfff;
    i64 rs1 = cpu_state.get_reg(inst.rs1());
    if (inst.rd() != 0) {
        u64 csr_val = cpu_state.csr.read(addr);
        cpu_state.set_reg(inst.rd(), static_cast<i64>(csr_val));
    }
    cpu_state.csr.write(addr, static_cast<u64>(rs1));
}

auto csrrs(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    u16 addr = static_cast<u16>(inst.imm()) & 0xfff;
    i64 rs1 = cpu_state.get_reg(inst.rs1());
    u64 csr_val = cpu_state.csr.read(addr);
    cpu_state.set_reg(inst.rd(), static_cast<i64>(csr_val));
    if (inst.rs1() != 0) {
        cpu_state.csr.write(addr, csr_val | static_cast<u64>(rs1));
    }
}

auto csrrc(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    u16 addr = static_cast<u16>(inst.imm()) & 0xfff;
    i64 rs1 = cpu_state.get_reg(inst.rs1());
    u64 csr_val = cpu_state.csr.read(addr);
    cpu_state.set_reg(inst.rd(), static_cast<i64>(csr_val));
    if (inst.rs1() != 0) {
        cpu_state.csr.write(addr, csr_val & ~static_cast<u64>(rs1));
    }
}

auto csrrwi(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    u16 addr = static_cast<u16>(inst.imm()) & 0xfff;
    if (inst.rd() != 0) {
        u64 csr_val = cpu_state.csr.read(addr);
        cpu_state.set_reg(inst.rd(), static_cast<i64>(csr_val));
    }
    cpu_state.csr.write(addr, static_cast<u64>(inst.rs1()));
}

auto csrrsi(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    u16 addr = static_cast<u16>(inst.imm()) & 0xfff;
    u64 csr_val = cpu_state.csr.read(addr);
    cpu_state.set_reg(inst.rd(), static_cast<i64>(csr_val));
    if (inst.rs1() != 0) {
        cpu_state.csr.write(addr, csr_val | static_cast<u64>(inst.rs1()));
    }
}

auto csrrci(hart_state& cpu_state, u32 raw) -> void {
    encoding_i inst(raw);
    u16 addr = static_cast<u16>(inst.imm()) & 0xfff;
    u64 csr_val = cpu_state.csr.read(addr);
    cpu_state.set_reg(inst.rd(), static_cast<i64>(csr_val));
    if (inst.rs1() != 0) {
        cpu_state.csr.write(addr, csr_val & ~static_cast<u64>(inst.rs1()));
    }
}

}
