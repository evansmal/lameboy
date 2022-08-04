#include "decoder.hpp"

#include <map>

InstructionDescription GetDescription(Byte opcode)
{
    if (INSTRUCTION_REGISTRY.contains(opcode))
    {
        const auto &description = INSTRUCTION_REGISTRY.at(opcode);
        return description;
    }
    else
    {
        throw std::runtime_error("Could not find instruction code " + ToHex(opcode) +
                                 " in the registry");
    }
}

Instruction Decode(Byte const *const buffer)
{
    const Byte opcode = buffer[0];
    const auto description = GetDescription(opcode);
    std::array<Byte, MAX_OPERANDS> operands{};
    for (int i = 1; i < description.length; i++)
    {
        operands[i] = buffer[i];
    }
    return {opcode, operands};
}

std::string ToString(const Instruction &instruction)
{
    const auto desc = GetDescription(instruction.opcode);
    std::stringstream ss;
    ss << "[" << desc.name << "] ";
    ss << std::setfill('0') << std::setw(2) << std::hex << int(instruction.opcode) << " ";
    for (int i = 0; i < desc.length - 1; i++)
    {
        ss << int(instruction.operands[i]) << " ";
    }
    return ss.str();
}
