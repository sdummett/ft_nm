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

#define OPTION_A (1 << 0)
#define OPTION_G (1 << 1)
#define OPTION_P (1 << 2)
#define OPTION_R (1 << 3)
#define OPTION_U (1 << 4)
#define OPTION_H (1 << 5)
#define OPTION_ERROR (1 << 6)

// Define the structure to hold the option data
typedef struct {
    const char short_opt;
    const char* long_opt;
} Option;

typedef struct Elf64_Sym_Nm {
	char *symbol_name;
	char *symbol_value;
	char symbol_type;
	struct Elf64_Sym_Nm *next;
} Elf64_Sym_Nm;

// get_opt.c
void get_opt(int ac, char **av, char *opts);
bool is_option_set(char *options, char option_flag);

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
char *unsignedlong_to_hex_string(unsigned long number);
char *convert_ulong_to_hex(unsigned long number, bool padding);
char *utohex(unsigned long nb);
char *utoascii(unsigned int n);
char *itoascii(int n);
bool isuppercase(int c);

// get_symbol_type.c
char get_symbol_type(void *f, Elf64_Sym *sym);

// get_section_header.c
Elf64_Shdr *get_section_header(void *f, int idx);

//print_symtab_entries.c
void print_symtab_entries(void *, Elf64_Shdr *, char *);

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
