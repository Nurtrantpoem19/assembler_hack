# Hack Assembler (Nand2Tetris Project 6)

This project is a C++ implementation of the Hack Assembler, developed as part of the Nand2Tetris course. It translates Hack assembly language (`.asm`) programs into binary machine code (`.hack`) executable on the Hack architecture.

## Overview

The code is divided into three main modules:

* **Parser Module:** Parses the `.asm` files line-by-line and extracts components without the operators.
* **Code Module:** Outputs the binary equivalent for each parsed component.
* **Symbol Table Module:** Stores address commands and labels with their respective memory addresses for reusability.

The `Assembler` class coordinates these modules to read an ASM file and generate a Hack file.

## Features

* **Two-Pass Process:**
* *First Pass:* Scans the file to store variables, labels, and their respective addresses.
* *Second Pass:* Translates instructions into binary, resolves addresses, removes labels, and generates the final output.


* **Support for:**
* Address commands and variables (`@address`)
* C-instructions (`dest=comp;jmp`)
* Label matching (`(label)`)
* Predefined symbols (`R0-R15`, `SCREEN`, `KBD`)



*Note: This implementation does not currently support syntax error reporting.*

## Project Structure

```text
.
├── CMakeLists.txt
├── include/assembler/
│   ├── Assembler.hpp
│   ├── code.hpp
│   ├── Parser.hpp
│   └── symbolTable.hpp
├── main/
├── src/
│   ├── Assembler.cpp
│   ├── code.cpp
│   ├── main.cpp
│   ├── Parser.cpp
│   └── SymbolTable.cpp
└── tests/
    ├── assembler_test.cpp
    ├── CMakeLists.txt
    ├── code_test.cpp
    ├── parser_test.cpp
    ├── symbol_test.cpp
    └── testing.vim

```

## Build

To build the program, follow these steps:

1. Create a build directory:
```bash
mkdir build
cd build

```


2. Configure and build:
```bash
cmake ..
cmake --build .

```



## How to Use

Once the binary is built, run the following command in the terminal:

```bash
./main file.asm

```

This will generate `file.hack` in the same directory as your input file.

## Example input and output
input.asm
```
@2
D=A
@3
D=D+A
@0
M=D
```
input.hack (output of main)
```
0000000000000010
1110110000010000
0000000000000011
1110000010010000
0000000000000000
1110001100001000
```
## Testing

This project includes unit tests for the Parser, Code, and Symbol Table modules using the **GoogleTest (gtest)** framework.

To run the tests:

1. Ensure you have built the project (see **Build**).
2. Execute `ctest` from the `build` directory:
```bash
cd build
ctest

```


Alternatively, you can run individual test binaries located in `build/tests/`.

## Symbol Handling

The assembler implements symbol resolution using a two-pass approach:

* **First Pass:** Assigns ROM addresses to every label `(label)` encountered.
* **Variables:** User-defined variables are assigned to RAM addresses starting at `16`, incrementing sequentially for each new variable discovered.

## Known Limitations

* **Symbol Collisions:** There is a known issue where label addresses and register references may collide (e.g., `@R10` and `@loop` mapped to line 10 may resolve to the same binary address).
* **Error Handling:** The assembler currently lacks syntax validation; it does not provide feedback for malformed input files.
* **Batch Processing:** The tool currently processes one file at a time. This can be extended via a simple shell script wrapper.

## License

This project is licensed under the [MIT License](https://www.google.com/search?q=LICENSE).

## Acknowledgements

Created as part of the [Nand2Tetris](https://www.nand2tetris.org/) course by Noam Nisan and Shimon Schocken.
