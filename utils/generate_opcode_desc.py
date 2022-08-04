import argparse 
import json


def to_desc_string(opcode, op):
    return f'ADD_DESCRIPTION({hex(opcode)}, "{op["Name"]}", {op["Length"]}, {op["TCyclesBranch"]})'

def generate_map(ops):
    res = '#define ADD_DESCRIPTION(code, name, length, cycles) {{code}, { code, name, length, cycles }}\n\n'
    res += 'const std::map<Byte, InstructionDescription> INSTRUCTION_REGISTRY = {'
    for i, op in enumerate(ops):
        res += f'    {to_desc_string(i, op)},\n'
    res += '};'
    return res

def to_enum_string(opcode, op):
    name = str(op["Name"]).upper().replace(" ", "_").replace(",", "_").replace("(", "V").replace(")", "").replace("+", "PLUS").replace("-", "X")
    return f'{name} = {hex(opcode)}'

def generate_list(ops):
    res = 'enum OpCode {\n'
    for i, op in enumerate(ops):
        if op["Name"] != "UNUSED":
            res += f'    {to_enum_string(i, op)},\n'
    res += '};'
    return res


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
        res += generate_list(unprefixed) + "\n\n"
        res += generate_map(unprefixed) + "\n\n"

        print(res)


if __name__ == '__main__':
    main()
