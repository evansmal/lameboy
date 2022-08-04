#pragma once

#include <array>
#include <string>

#include "types.hpp"

const unsigned int ENTRYPOINT_LENGTH = 4;
const unsigned int LOGO_LENGTH = 48;
const unsigned int MAX_ROM_SIZE = 0x10000;

enum class CartridgeType : uint16_t
{
    ROM_ONLY,
    MBC1,
    MBC1_RAM,
    MBC1_RAM_BATTERY,
    MBC2
};

struct HeaderChecksum
{
    uint8_t computed;
    uint8_t actual;
    [[nodiscard]] bool Passed() const { return (computed == actual); }
};

struct Cartridge
{
    std::array<Byte, ENTRYPOINT_LENGTH> entrypoint;
    std::array<Byte, LOGO_LENGTH> logo;
    std::string title;
    CartridgeType type;
    HeaderChecksum checksum;
    std::array<Byte, MAX_ROM_SIZE> rom;
};

Cartridge LoadCartridge(const std::string &filepath);

std::string GetInfo(const Cartridge &cartridge);

