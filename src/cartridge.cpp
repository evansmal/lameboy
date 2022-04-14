
#include <fstream>
#include <iostream>
#include <vector>

#include "cartridge.hpp"

static std::vector<Byte> LoadBinaryFile(const std::string &filepath)
{
    std::ifstream file(filepath, std::ifstream::binary);
    return {std::istreambuf_iterator<char>(file), {}};
}
const unsigned int ENTRYPOINT_START = 0x0100;

const unsigned int LOGO_START = 0x0104;

const unsigned int TITLE_START = 0x0134;
const unsigned int TITLE_LENGTH = 16;

const unsigned int CARTIDGE_TYPE_START = 0x0147;

const unsigned int CHECKSUM_START = 0x0134;
const unsigned int CHECKSUM_END = 0x014c;
const unsigned int CHECKSUM_ACTUAL_START = 0x014d;

template <size_t N>
void Copy(const std::vector<Byte> &src, std::array<Byte, N> &dst, unsigned int pos)
{
    std::copy(src.cbegin() + pos, src.cbegin() + pos + N, dst.begin());
}

std::string ToString(const std::vector<Byte> &src, unsigned int pos, unsigned int len)
{
    return {src.cbegin() + pos, src.cbegin() + pos + len};
}

uint8_t ComputeHeaderChecksum(const std::vector<Byte> &file)
{
    uint8_t x = 0;
    for (unsigned int i = CHECKSUM_START; i <= CHECKSUM_END; i++)
    {
        x = x - file[i] - 1;
    }
    return x;
}

Cartridge LoadCartridge(const std::string &filepath)
{
    const auto file = LoadBinaryFile(filepath);

    Cartridge cartridge{};
    cartridge.logo = {};
    Copy(file, cartridge.entrypoint, ENTRYPOINT_START);
    Copy(file, cartridge.logo, LOGO_START);

    cartridge.title = ToString(file, TITLE_START, TITLE_LENGTH);

    cartridge.type = CartridgeType(file[CARTIDGE_TYPE_START]);

    cartridge.checksum = {ComputeHeaderChecksum(file), file[CHECKSUM_ACTUAL_START]};

    Copy(file, cartridge.rom, 0);

    return cartridge;
}
