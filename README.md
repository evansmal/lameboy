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

## References

- [Game Boy: Complete Technical Reference]( https://gekkio.fi/files/gb-docs/gbctr.pdf )
- [Pan Docs](https://gbdev.io/pandocs)
- [gbops, an accurate opcode table for the Game Boy](https://izik1.github.io/gbops/)
