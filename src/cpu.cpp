#include "cpu.hpp"
#include "decoder.hpp"
#include "types.hpp"

uint16_t GetU16(const Operands &operands, int offset = 0)
{
    uint8_t lower = operands[offset + 0];
    uint16_t upper = operands[offset + 1];
    return ((upper << 8) | lower);
}

Instruction Fetch(const CPU &cpu, const Cartridge &cartridge)
{
    Byte const *const opcode = &cartridge.rom[cpu.registers.pc];
    std::cout << ToString(Decode(opcode)) << std::endl;
    return Decode(opcode);
}

void Run(const Cartridge &cartridge)
{
    CPU cpu{};
    cpu.registers.pc = 0x0100;

    while (true)
    {
        const Instruction instruction = Fetch(cpu, cartridge);
        switch (instruction.opcode)
        {
        case NOP: {
            cpu.registers.pc++;
            break;
        }
        case JP_U16: {
            const uint16_t dst = GetU16(instruction.operands);
            cpu.registers.pc = dst;
            break;
        }
        case RET_NZ: {
            break;
        }
        default: {
            throw std::runtime_error("Invalid instruction type encountered: " + ToHex(instruction.opcode));
        }
        }
    }
}
