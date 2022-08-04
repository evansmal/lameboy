#pragma once

#include <cstdint>
#include <string>

#include "print.h"
#include "types.hpp"


struct InstructionDescription
{
    Byte opcode;
    std::string name;
    uint16_t length;
    uint16_t cycles;
};

#include "instructions.hpp"

const unsigned int MAX_OPERANDS = 16;

using Operands = std::array<Byte, MAX_OPERANDS>;

struct Instruction
{
    Byte opcode;
    Operands operands;
};

InstructionDescription GetDescription(Byte opcode);

Instruction Decode(Byte const *const buffer);

std::string ToString(const Instruction &instruction);

