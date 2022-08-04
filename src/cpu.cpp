#include "cpu.hpp"

uint16_t GetU16(Byte const *const buffer)
{
    uint8_t lower = buffer[0];
    uint16_t upper = buffer[1];
    return ((upper << 8) | lower);
}

Instruction Fetch(const CPU &cpu, const Cartridge &cartridge)
{
    uint8_t opcode = cartridge.rom[cpu.registers.pc];
    switch (opcode)
    {
    case OpCode::NOP: {
        return nop{};
    }
    case OpCode::JP: {
        return jp{GetU16(&cartridge.rom[cpu.registers.pc + 1])};
    }
    default:
        throw std::runtime_error("Could not decode instruction at " + ToHex(opcode));
    }
}

void Run(const Cartridge &cartridge)
{
    CPU cpu{};
    cpu.registers.pc = 0x0100;

    while (true)
    {
        const Instruction instruction = Fetch(cpu, cartridge);
        if (std::holds_alternative<nop>(instruction))
        {
            cpu.registers.pc++;
        }
        else if (std::holds_alternative<jp>(instruction))
        {
            const auto &jump = std::get<jp>(instruction);
            cpu.registers.pc = jump.dst;
        }
        else
        {
            throw std::runtime_error("Invalid instruction type encountered");
        }
    }
}
