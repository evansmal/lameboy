#include <cstdint>
#include <iostream>
#include <variant>

#include "cartridge.hpp"

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

struct Add
{
};

using Instruction = std::variant<Add>;

int main(int argc, char **argv)
{
    if (argc != 2) return EXIT_FAILURE;

    const auto cartridge = LoadCartridge(argv[1]);

    return 0;
}
