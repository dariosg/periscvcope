#include <instructions.hh>
#include <memory.hh>

using namespace instrs;
using namespace mem;

// ToDo use the type instead of RISC-V funct3 field?
// assume little endian
// LW 0b010
template<>
void instrs::execute_load<0b010>(mem::memory& mem, processor & proc,
    mem::address_t addr, uint8_t rd)
{
  assert((addr & 0b11) == 0); // ensure alignment
  proc.write_reg(rd, mem.read<uint32_t>(addr));
}

// LBU 100
template<>
void instrs::execute_load<0b100>(mem::memory& mem, processor & proc,
    mem::address_t addr, uint8_t rd)
{
  // no sign extension
  uint32_t val = mem.read<uint8_t>(addr);
  proc.write_reg(rd, val);
}

// LB 000
template<>
void instrs::execute_load<0b000>(mem::memory& mem, processor & proc,
    mem::address_t addr, uint8_t rd)
{
  uint32_t val = static_cast<uint32_t>(sign_extend<int32_t, 
		  sizeof(uint8_t)*8>(mem.read<uint8_t>(addr)));
  proc.write_reg(rd, val);
}

// LH
template<>
void instrs::execute_load<0b001>(mem::memory& mem, processor & proc,
    mem::address_t addr, uint8_t rd)
{
  assert((addr & 0b1) == 0); // ensure alignment
  // perform sign extension
  uint32_t val = static_cast<uint32_t>(sign_extend<int32_t,
           sizeof(uint16_t)*8>(mem.read<uint16_t>(addr)));
  proc.write_reg(rd, val);
}

// LHU
template<>
void instrs::execute_load<0b101>(mem::memory& mem, processor & proc,
    mem::address_t addr, uint8_t rd)
{
  assert((addr & 0b1) == 0); // ensure alignment
  // perform sign extension
  uint32_t val = mem.read<uint16_t>(addr);
  proc.write_reg(rd, val);
}


uint32_t instrs::load(memory& mem, processor & proc, uint32_t bitstream) {

  i_instruction ii{bitstream};

  // compute src address
  address_t src = proc.read_reg(ii.rs1()) + ii.imm12();

  // ToDo refactor with templates
  switch(ii.funct3()) {
    case 0b010: execute_load<0b010>(mem, proc, src, ii.rd()); break;
    case 0b000: execute_load<0b000>(mem, proc, src, ii.rd()); break;
    case 0b001: execute_load<0b001>(mem, proc, src, ii.rd()); break;
    case 0b100: execute_load<0b100>(mem, proc, src, ii.rd()); break;
    case 0b101: execute_load<0b101>(mem, proc, src, ii.rd()); break;
  }
  // return next instruction
  return proc.next_pc();
}

// SB
template<>
void instrs::execute_store<0b000>(mem::memory& mem, processor& proc,
    mem::address_t addr, uint8_t rs2)
{
  mem.write<uint8_t>(addr, static_cast<uint8_t>(proc.read_reg(rs2)));
}

// SH
template<>
void instrs::execute_store<0b001>(mem::memory& mem, processor& proc,
    mem::address_t addr, uint8_t rs2)
{
  mem.write<uint16_t>(addr, static_cast<uint16_t>(proc.read_reg(rs2)));
}

// SW
template<>
void instrs::execute_store<0b010>(mem::memory& mem, processor& proc,
    mem::address_t addr, uint8_t rs2)
{
  mem.write<uint32_t>(addr, proc.read_reg(rs2));
}

uint32_t instrs::store(memory& mem, processor & proc, uint32_t bitstream) {

  s_instruction si{bitstream};

  // compute dst address
  address_t src = proc.read_reg(si.rs1()) + si.imm();

  // ToDo refactor with templates
  switch(si.funct3()) {
    case 0b000: execute_store<0b000>(mem, proc, src, si.rs2()); break; // SB
    case 0b001: execute_store<0b001>(mem, proc, src, si.rs2()); break; // SH
    case 0b010: execute_store<0b010>(mem, proc, src, si.rs2()); break; // SW
  }
  // return next instruction
  return proc.next_pc();
}

