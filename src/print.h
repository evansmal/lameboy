#pragma once

#include <array>
#include <iostream>

#include "types.hpp"

template <size_t N>
void PrintBuffer(std::array<Byte, N> &buffer)
{
    for (const auto &b : buffer)
    {
        std::cout << std::hex << int(b) << " ";
    }
    std::cout << std::endl;
}
