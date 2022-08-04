#include <cartridge.hpp>
#include <cpu.hpp>

#include <iostream>
#include <string>

void ExecuteTestCase(const std::string &test_dir, const std::string &test_name)
{

    const std::string test_filepath = test_dir + "/" + test_name;
    std::cout << "Loading test case: " << test_filepath << std::endl;

    const auto cartridge = LoadCartridge(test_filepath);

    std::cout << GetInfo(cartridge) << std::endl;
    Run(cartridge);
}

int main()
{
    ExecuteTestCase("./test/mooneye-test-suite", "acceptance/instr/daa.gb");
    return EXIT_SUCCESS;
}
