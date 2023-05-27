#include "ft_nm.h"

static char *get_symbol_name(void *f, Elf64_Shdr *symtab_hdr, uint32_t st_name);
static Elf64_Sym *get_symbol(void *f, Elf64_Shdr *symtab_hdr, uint32_t idx);

void print_symtab_entries(void *f, Elf64_Shdr * symtab_hdr) {
	uint32_t symtab_entries_num = symtab_hdr->sh_size / symtab_hdr->sh_entsize;

	Elf64_Ehdr *ehdr= (Elf64_Ehdr *)f;
	for (uint32_t i = 0; i < symtab_entries_num; i++) {

		Elf64_Sym *symbol = get_symbol(f, symtab_hdr, i);
		char *symbol_name = get_symbol_name(f, symtab_hdr, symbol->st_name);

		char *section_name = NULL;
		if (symbol->st_shndx != SHN_UNDEF && symbol->st_shndx != SHN_ABS && \
				symbol->st_shndx != SHN_COMMON && symbol->st_shndx != SHN_XINDEX) {
			Elf64_Shdr *hdr = (Elf64_Shdr *)(f + ehdr->e_shoff + (symbol->st_shndx * ehdr->e_shentsize));
			Elf64_Shdr *shstrtb = get_section_header(f, ehdr->e_shstrndx);
			section_name = (char *)(f + shstrtb->sh_offset + hdr->sh_name);
		}
		printf("%016lx %s %s\n", symbol->st_value, section_name, symbol_name);
	}
}

static char *get_symbol_name(void *f, Elf64_Shdr *symtab_hdr, uint32_t st_name) {
	Elf64_Shdr *strtab_hdr = get_section_header(f, symtab_hdr->sh_link);
	return f + strtab_hdr->sh_offset + st_name;
}

static Elf64_Sym *get_symbol(void *f, Elf64_Shdr *symtab_hdr, uint32_t idx) {
	return f + (symtab_hdr->sh_offset + (idx * symtab_hdr->sh_entsize));
}
