#include "ft_nm.h"

static char *get_symbol_name(void *f, Elf64_Shdr *symtab_hdr, uint32_t st_name);
static Elf64_Sym *get_symbol(void *f, Elf64_Shdr *symtab_hdr, uint32_t idx);
static void print_entry(Elf64_Sym *symbol, char *section_name, char *symbol_name);
static char* get_sym_value(Elf64_Sym *sym);
void debug_st_info_st_other(Elf64_Sym *sym);

void print_symtab_entries(void *f, Elf64_Shdr * symtab_hdr) {
	uint32_t symtab_entries_num = symtab_hdr->sh_size / symtab_hdr->sh_entsize;

	Elf64_Ehdr *ehdr= (Elf64_Ehdr *)f;
	for (uint32_t i = 1; i < symtab_entries_num; i++) {

		Elf64_Sym *symbol = get_symbol(f, symtab_hdr, i);
		char *symbol_name = get_symbol_name(f, symtab_hdr, symbol->st_name);

		char *section_name = NULL;
		if (symbol->st_shndx != SHN_UNDEF && symbol->st_shndx != SHN_ABS && \
				symbol->st_shndx != SHN_COMMON && symbol->st_shndx != SHN_XINDEX) {
			Elf64_Shdr *hdr = (Elf64_Shdr *)(f + ehdr->e_shoff + (symbol->st_shndx * ehdr->e_shentsize));
			Elf64_Shdr *shstrtb = get_section_header(f, ehdr->e_shstrndx);
			section_name = (char *)(f + shstrtb->sh_offset + hdr->sh_name);
		}
		print_entry(symbol, section_name, symbol_name);
	}
}

#include "string.h"
char get_type(char *section_name) {
	char t;
	if(!section_name)
		return 0;
	if (strcmp(section_name, ".text") == 0)
		t = 't';
	else if (strcmp(section_name, ".bss") == 0)
		t = 'b';
	else if (strcmp(section_name, ".data") == 0)
		t = 'd';
	else if (strcmp(section_name, ".rodata") == 0)
		t = 'n';
	else if (strcmp(section_name, ".note-GNU-stack") == 0)
		t = 'p';
	else
		t = 0;;
	return t;
}

static void print_entry(Elf64_Sym *symbol, char *section_name, char *symbol_name) {
	char type = get_type(section_name);
	char *st_value= get_sym_value(symbol);

	if (ELF64_ST_TYPE(symbol->st_info) == STT_FILE)
		return;

//	debug_st_info_st_other(symbol);
	if (type)
		printf("%s %c %s\n", st_value, type, symbol_name);
	else
		printf("%s %s %s\n",st_value, section_name, symbol_name);
	free(st_value);
}

static char* get_sym_value(Elf64_Sym *sym) {
	// strdup & sprintf is forbidden
	if (sym->st_value == 0)
		return strdup("                ");
	char *str = malloc(20);
	sprintf(str, "%016lx", sym->st_value);
	return str;
}

static char *get_symbol_name(void *f, Elf64_Shdr *symtab_hdr, uint32_t st_name) {
	Elf64_Shdr *strtab_hdr = get_section_header(f, symtab_hdr->sh_link);
	return f + strtab_hdr->sh_offset + st_name;
}

static Elf64_Sym *get_symbol(void *f, Elf64_Shdr *symtab_hdr, uint32_t idx) {
	return f + (symtab_hdr->sh_offset + (idx * symtab_hdr->sh_entsize));
}

void debug_st_info_st_other(Elf64_Sym *sym) {
		switch(ELF64_ST_BIND(sym->st_info)) {
		case STB_LOCAL:
			printf("STB_LOCAL ");
			break;
		case STB_GLOBAL:
			printf("STB_GLOBAL ");
			break;
		case STB_WEAK:
			printf("STB_WEAK ");
			break;
		case STB_LOPROC:
			printf("STB_LOPROC ");
			break;
		case STB_HIPROC:
			printf("STB_HIPROC ");
			break;
		default:
			printf("STB not found, value : %d ", sym->st_info);
	}

	switch(ELF64_ST_TYPE(sym->st_info)) {
		case STT_NOTYPE:
			printf("STT_NOTYPE ");
			break;
		case STT_OBJECT:
			printf("STT_OBJECT ");
			break;
		case STT_FUNC:
			printf("STT_FUNC ");
			break;
		case STT_SECTION:
			printf("STT_SECTION ");
			break;
		case STT_FILE:
			printf("STT_FILE ");
			break;
		case STT_LOPROC:
			printf("STT_LOPROC ");
			break;
		case STT_HIPROC:
			printf("STT_HIPROC ");
			break;
		default:
			printf("STT not found, value : %d ", sym->st_info);
	}

	switch(ELF64_ST_VISIBILITY(sym->st_other)) {
		case STV_DEFAULT:
			printf("STV_DEFAULT ");
			break;
		case STV_INTERNAL:
			printf("STV_INTERNAL ");
			break;
		case STV_HIDDEN:
			printf("STV_HIDDEN ");
			break;
		case STV_PROTECTED:
			printf("STV_PROTECTED ");
			break;
		default:
			printf("not found, value %d ", sym->st_other);
	}
}
