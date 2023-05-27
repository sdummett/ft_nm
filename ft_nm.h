#ifndef FT_NM_H
#define FT_NM_H

#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <elf.h>

// tools
#include <stdio.h>

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

#endif
