# lameboy

Gameboy emulator written in C++

## Getting Started

Start by cloning and building the project:

```sh
git clone https://github.com/evansmal/lameboy.git
cd lameboy && mkdir build && cd build
cmake .. && make
```

Run using the filepath to your ROM: 

```sh
./build/lameboy <rom_filepath>
```

## Generating `instructions.hpp`

We use the JSON description from [this project](https://izik1.github.io/gbops/) to code generate a header containing all of the opcodes to avoid maintaining this manually. To regenerate this header, [download the JSON source](https://raw.githubusercontent.com/izik1/gbops/master/dmgops.json) locally and run the following command:

```sh
python3 utils/generate_opcode_desc.py ops.json > src/instructions.cpp
```

## References

- [Game Boy: Complete Technical Reference]( https://gekkio.fi/files/gb-docs/gbctr.pdf )
- [Pan Docs](https://gbdev.io/pandocs)
- [gbops, an accurate opcode table for the Game Boy](https://izik1.github.io/gbops/)
