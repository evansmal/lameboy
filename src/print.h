#pragma once

#include <array>
#include <iostream>
#include <sstream>
#include <iomanip>

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

template <typename T>
std::string ToHex(T value)
{
    std::stringstream stream;
    stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << int(value);
    return stream.str();
}
