#include <cstdint>
#include <iostream>
#include <variant>
#include <vector>

#include "cartridge.hpp"
#include "print.h"
#include "types.hpp"

struct Flags
{
    bool zero;
    bool subtract;
    bool half_carry;
    bool carry;
};

struct Registers
{
    uint16_t sp;
    uint16_t pc;
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t f;
    uint8_t h;
    uint8_t l;
};

struct CPU
{
    Registers registers;
    void Step() {}
};

struct Noop
{
};

struct Jump
{
    uint16_t dst;
};

enum InstructionCode
{
    NOOP = 0x00,
    JUMP = 0xc3,
};

using Instruction = std::variant<Noop, Jump>;

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
    case InstructionCode::NOOP: {
        return Noop{};
    }
    case InstructionCode::JUMP: {
        return Jump{GetU16(&cartridge.rom[cpu.registers.pc + 1])};
    }
    default:
        throw std::runtime_error("Could not decode instruction at " + ToHex(opcode));
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) return EXIT_FAILURE;
    const auto cartridge = LoadCartridge(argv[1]);
    std::cout << "Game title: " << cartridge.title << std::endl;
    std::cout << "Cartridge type: " << int(cartridge.type) << std::endl;
    std::cout << "Checksum: " << int(cartridge.checksum.actual) << " "
              << int(cartridge.checksum.computed) << " " << cartridge.checksum.Passed()
              << std::endl;

    CPU cpu{};
    cpu.registers.pc = 0x0100;

    while (true)
    {
        const Instruction instruction = Fetch(cpu, cartridge);
        if (std::holds_alternative<Noop>(instruction))
        {
            cpu.registers.pc++;
        }
        else if (std::holds_alternative<Jump>(instruction))
        {
            const auto &jump = std::get<Jump>(instruction);
            std::cout << "JUMPING TO " << int(jump.dst) << std::endl;
            cpu.registers.pc = jump.dst;
        }
        else
        {
            throw std::runtime_error("Invalid instruction type encountered");
        }
    }

    return 0;
}
