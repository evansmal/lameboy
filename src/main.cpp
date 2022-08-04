#include <cstdint>
#include <filesystem>
#include <iostream>
#include <variant>
#include <vector>

#include "cpu.hpp"
#include "cartridge.hpp"
#include "print.h"
#include "types.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Expected path to ROM. Exiting." << std::endl;
        std::cout << "Usage: ./lameboy <rom>" << std::endl;
        return EXIT_FAILURE;
    }

    if (std::filesystem::exists(argv[1]) == false)
    {
        std::cout << "ROM does not exist at path " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    const auto cartridge = LoadCartridge(argv[1]);
    std::cout << GetInfo(cartridge) << std::endl;
    Run(cartridge);
    return 0;
}
