# ft_nm

## Description

ft_nm is a command-line program written in C that emulates the behavior of the nm command on ELF binaries. It is designed to run on a Linux system and supports various architectures such as x86_32 and x64. The program allows users to analyze object files and shared libraries (.so) to retrieve information about symbols defined or referenced within the binary.

The primary objective of ft_nm is to display symbol tables from ELF binaries, providing valuable insights into the binary's structure. By examining these symbols, developers can gain a better understanding of the binary's code organization, variable and function names, and their corresponding memory addresses.

When executed, ft_nm parses the given binary file and generates a formatted output that closely resembles the output of the nm command. The output includes details such as the symbol's type, address, and name. By default, the symbols are displayed in a sorted order, making it easier to navigate through the binary's symbol table. However, an optional flag allows users to disable sorting and view symbols in the order they appear in the binary.

ft_nm ensures robust error handling to prevent unexpected program termination. It meticulously validates inputs, handles edge cases, and performs thorough error checks throughout its execution. This attention to detail guarantees a reliable and stable program that adheres to strict coding standards.

## Usage

To run ft_nm, use the following command:

```bash
./ft_nm [options] <binary_file>
```

Replace [options] with any of the following optional flags:

    -a, --debug-syms       Display all symbols, including local symbols.
    -g, --extern-only      Display only external symbols.
    -u, --undefined-only   Display only undefined symbols.
    -r, --reverse-sort     Sort the symbols in reverse order.
    -p, --no-sort          Do not sort the symbols, display in the order they appear in the binary.
    -h, --help             Display this information

Replace <binary_file> with the path to the ELF binary you want to analyze.
