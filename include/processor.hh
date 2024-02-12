#pragma once

#include <array>
#include <cassert>
#include <cstdint>
#include <cstddef>

class processor {


  private:
  constexpr static size_t num_regs = 32;
  std::array<uint32_t, num_regs> _reg_file;
  uint32_t _pc;

  public:
  constexpr static size_t sp = 2;

  processor()
  {
   for(auto& e: _reg_file) {
    e = 0;
   }
  }

  // FIXME use contracts C++20
  constexpr uint32_t read_reg(size_t i) const { assert(i<32); return _reg_file[i]; }
  void write_reg(size_t i, uint32_t val) { assert(i<32); if(i>0) { _reg_file[i] = val; } }

  constexpr uint32_t read_pc() const { return _pc; }
  uint32_t next_pc() { _pc+=4; return _pc; }
  void write_pc(uint32_t val) { _pc = val; };
};
