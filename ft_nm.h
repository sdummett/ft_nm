#ifndef FT_NM_H
#define FT_NM_H

#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <elf.h>
#include <stdbool.h>

// tools
#include <stdio.h>
#include <string.h>

// get_symbol_type.c
char get_symbol_type(void *f, Elf64_Sym *sym);

// get_section_header.c
Elf64_Shdr *get_section_header(void *f, int idx);

//print_symtab_entries.c
void print_symtab_entries(void *, Elf64_Shdr *);

// debug_elf_header.c
void debug_elf_header(Elf64_Ehdr);

// debug_elf_section.c
void debug_elf_section_header(Elf64_Shdr);

// debug_elf_symtab.c
void debug_elf_symtab(Elf64_Sym);

// debug_elf_symbol.c
void debug_sh_type_sh_flags(void *f, Elf64_Sym *sym);
void debug_st_info_st_other(Elf64_Sym *sym);

#endif
