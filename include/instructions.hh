#pragma once

#include <cstdint>
#include <functional>

#include <memory.hh>
#include <processor.hh>

// extracted from the riscv-spec-20191213.pdf

namespace instrs {

enum class type {base, r, i, s, b, u, j};

class instruction {
    protected:
        instrs::type _type;
        uint32_t _bitstream;
    public:
        // check Figure 2.4 from the manual
        constexpr uint32_t bits(size_t lsb, size_t len) const
        {
            return (_bitstream >> lsb) & ((static_cast<uint32_t>(1) << len)-1);
        }
        instruction(uint32_t bitstream, instrs::type type=type::base) : _type(type),
        _bitstream(bitstream) {}

        constexpr instrs::type type() const { return _type; }
        constexpr uint8_t opcode() const { return bits(0,7); }
};

class r_instruction : public instruction {
    public:
        r_instruction(uint32_t bitstream) :
            instruction(bitstream, type::r) {}
        constexpr uint8_t rd() const { return bits(7, 5); }
        constexpr uint8_t funct3() const { return bits(12, 3); }
        constexpr uint8_t rs1() const { return bits(15, 5); }
        constexpr uint8_t rs2() const { return bits(20, 5); }
        constexpr uint32_t funct7() const { return bits(25, 7); }
};

class i_instruction : public instruction {
    // ...
};

class s_instruction : public instruction {
    // ...
};

class b_instruction : public instruction {
    // ...
};

class u_instruction : public instruction {
    // ...
};

class j_instruction : public instruction {
    // ...
};


} // namespace instrs
