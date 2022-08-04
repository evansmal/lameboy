import argparse 
import json


def to_string(opcode, op):
    """
    Generate a string that we can use in the C++ code.
    For example: ADD_DESCRIPTION(0x00, "JP", 1, 4),
    """
    return f'ADD_DESCRIPTION({hex(opcode)}, "{op["Name"]}", {op["Length"]}, {op["TCyclesBranch"]})'

def main():
    parser = argparse.ArgumentParser(description="This script can be \
            used to generate the INSTRUCTION_REGISTRY table from a JSON \
            file containing all of the metadata. For now, it assumes we're \
            using the file found here https://github.com/izik1/gbops/blob/master/dmgops.json")

    parser.add_argument("input", metavar="I", type=str, 
                        help="The JSON file to be used as input")
    args = parser.parse_args()

    with open(args.input) as json_file:

        json_data = json.load(json_file)

        unprefixed = json_data["Unprefixed"]
        prefixed = json_data["CBPrefixed"]

        res = '#pragma once\n\n#include "decoder.hpp"\n#include <map>\n\n'
        res += '#define ADD_DESCRIPTION(code, name, length, cycles) {{code}, { code, name, length, cycles }}\n\n'
        res += 'namespace lb::decoder {\n\n'
        res += 'const std::map<Byte, InstructionDescription> INSTRUCTION_REGISTRY = {'
        for i, op in enumerate(unprefixed):
            res += f'\t{to_string(i, op)},\n'
        res += '};\n\n'
        res += '}\n'

        print(res)


if __name__ == '__main__':
    main()
