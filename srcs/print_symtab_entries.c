#include "ft_nm.h"

static char *get_symbol_name(void *f, Elf64_Shdr *symtab_hdr, uint32_t st_name);
static Elf64_Sym *get_symbol(void *f, Elf64_Shdr *symtab_hdr, uint32_t idx);
static char* get_symbol_value(Elf64_Sym *sym);

void print_symtab_entries(void *f, Elf64_Shdr * symtab_hdr) {
	uint32_t symtab_entries_num = symtab_hdr->sh_size / symtab_hdr->sh_entsize;

	for (uint32_t i = 1; i < symtab_entries_num; i++) {
		Elf64_Sym *symbol = get_symbol(f, symtab_hdr, i);
		int type = ELF64_ST_TYPE(symbol->st_info);
		if (type == STT_FILE || type == STT_SECTION)
			continue;
		char *symbol_name = get_symbol_name(f, symtab_hdr, symbol->st_name);
		char *symbol_value= get_symbol_value(symbol);
		char symbol_type = get_symbol_type(f, symbol);

		#ifdef DEBUG
			debug_st_info_st_other(symbol);
			debug_sh_type_sh_flags(f, symbol);
		#endif
		printf("%s %c %s\n", symbol_value, symbol_type, symbol_name);
		free(symbol_value);
	}
}

static char* get_symbol_value(Elf64_Sym *sym) {

	// strdup & sprintf is forbidden
	if (sym->st_shndx == SHN_UNDEF)
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
