#ifndef FT_NM_H
#define FT_NM_H

#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <elf.h>
#include <stdbool.h>
#include <stdarg.h>
#include <errno.h>

// tools
#include <stdio.h>
#include <string.h>

typedef struct Elf64_Sym_Nm {
	char *symbol_name;
	char *symbol_value;
	char symbol_type;
	struct Elf64_Sym_Nm *next;
} Elf64_Sym_Nm;

// stringutils.c
int stringlen(const char *str);
void printerror(const char* message);
const char* stringerror(int errnum);
int stringcmp(const char* str1, const char* str2);
char *stringdup(const char *str);
void printfmt(int fd, char *fmt, ...);
size_t stringcat(char *dest, const char *src);
void sprintfmt(char *str, char *fmt, ...);
void *memoryset(void *s, int c, size_t n);
char* unsignedlong_to_hex_string(unsigned long number);
char* convert_ulong_to_hex(unsigned long number, bool padding);

// utohex.c
char	*utohex(unsigned long nb);

// utoasc.c
char	*utoascii(unsigned int n);

// itoascii.c
char	*itoascii(int n);

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
