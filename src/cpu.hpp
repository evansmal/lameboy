#pragma once

#include "print.h"
#include "cartridge.hpp"
#include "types.hpp"

#include <cstdint>
#include <variant>

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

void Run(const Cartridge &cartridge);

