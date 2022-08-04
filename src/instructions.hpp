#pragma once

#include <cstdint>
#include <variant>

struct nop
{
};

struct jp
{
    uint16_t dst;
};

struct ld_sp_u16 {

};

enum OpCode
{
    NOP = 0x00,
    JP = 0xc3,
    LD_SP_U16 = 0x31,
};

using Instruction  = std::variant<nop, jp, ld_sp_u16>;
