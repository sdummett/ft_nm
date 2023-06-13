#include "ft_nm.h"

static bool check_x32_symbol(Elf32_Ehdr *ehdr, off_t st_size, Elf32_Shdr *symtab_hdr, Elf32_Sym *symbol) {
	Elf32_Shdr *strtab_hdr = get_section_header_x32((void *)ehdr, symtab_hdr->sh_link);
	long unsigned int addr_max = (long unsigned int)ehdr + st_size;

	if ((long unsigned int)strtab_hdr + sizeof(Elf32_Shdr) > addr_max)
		return false;

	char *name = get_symbol_name_x32((void *)ehdr, symtab_hdr, symbol->st_name);
	while ((long unsigned int)name != addr_max && *name != '\0')
		name++;
	if ((long unsigned int)name > addr_max)
		return false;

	return true;
}

static bool check_x32_symtab(Elf32_Ehdr *ehdr, off_t st_size, Elf32_Shdr *symtab_hdr) {
	if (symtab_hdr->sh_entsize == 0)
		return true;

	uint32_t symtab_entries_num = symtab_hdr->sh_size / symtab_hdr->sh_entsize;

	if (symtab_entries_num - 1 && \
			symtab_hdr->sh_offset + (symtab_entries_num + symtab_hdr->sh_entsize) > (long unsigned int)st_size)
		return false;


	long unsigned int addr_max = (long unsigned int)ehdr + st_size;
	for (uint32_t i = 1; i < symtab_entries_num; i++) {
		Elf32_Sym *symbol = get_symbol_x32((void *)ehdr, symtab_hdr, i);

		if ((long unsigned int)symbol + sizeof(Elf32_Sym) > addr_max)
			return false;
		if (!check_x32_symbol(ehdr, st_size, symtab_hdr, symbol))
			return false;
	}

	return true;
}

bool check_x32_elf(Elf32_Ehdr *ehdr, off_t st_size) {
	if (ehdr->e_shoff + (ehdr->e_shentsize * ehdr->e_shnum) > (long unsigned int)st_size)
		return false;

	if (ehdr->e_shstrndx + 1 > ehdr->e_shnum)
		return false;

	for (int i = 0; i < ehdr->e_shnum; i++) {
		Elf32_Shdr *symtab_hdr = get_section_header_x32((void *)ehdr, i);
		if (symtab_hdr->sh_type == SHT_SYMTAB && !check_x32_symtab(ehdr, st_size, symtab_hdr))
			return false;
	}

	return true;
}

/* --------------------------------------------------- */

static bool check_x64_symbol(Elf64_Ehdr *ehdr, off_t st_size, Elf64_Shdr *symtab_hdr, Elf64_Sym *symbol) {
	Elf64_Shdr *strtab_hdr = get_section_header_x64((void *)ehdr, symtab_hdr->sh_link);
	long unsigned int addr_max = (long unsigned int)ehdr + st_size;

	if ((long unsigned int)strtab_hdr + sizeof(Elf64_Shdr) > addr_max)
		return false;

	char *name = get_symbol_name_x64((void *)ehdr, symtab_hdr, symbol->st_name);
	while ((long unsigned int)name != addr_max && *name != '\0')
		name++;
	if ((long unsigned int)name > addr_max)
		return false;

	return true;
}

static bool check_x64_symtab(Elf64_Ehdr *ehdr, off_t st_size, Elf64_Shdr *symtab_hdr) {
	if (symtab_hdr->sh_entsize == 0)
		return true;

	uint32_t symtab_entries_num = symtab_hdr->sh_size / symtab_hdr->sh_entsize;

	if (symtab_entries_num - 1 && \
			symtab_hdr->sh_offset + (symtab_entries_num + symtab_hdr->sh_entsize) > (long unsigned int)st_size)
		return false;

	long unsigned int addr_max = (long unsigned int)ehdr + st_size;
	for (uint32_t i = 1; i < symtab_entries_num; i++) {
		Elf64_Sym *symbol = get_symbol_x64((void *)ehdr, symtab_hdr, i);

		if ((long unsigned int)symbol + sizeof(Elf64_Sym) > addr_max)
			return false;
		if (!check_x64_symbol(ehdr, st_size, symtab_hdr, symbol))
			return false;
	}

	return true;
}

bool check_x64_elf(Elf64_Ehdr *ehdr, off_t st_size) {
	if (ehdr->e_shoff + (ehdr->e_shentsize * ehdr->e_shnum) > (long unsigned int)st_size)
		return false;

	if (ehdr->e_shstrndx + 1 > ehdr->e_shnum)
		return false;

	for (int i = 0; i < ehdr->e_shnum; i++) {
		Elf64_Shdr *symtab_hdr = get_section_header_x64((void *)ehdr, i);
		if (symtab_hdr->sh_type == SHT_SYMTAB && !check_x64_symtab(ehdr, st_size, symtab_hdr))
			return false;
	}

	return true;
}

/* --------------------------------------------------- */

int check_elf_header(Elf64_Ehdr *ehdr, off_t st_size) {
	// Implicitly checking the size of ELF32 Header (52 bytes)
	if (st_size < 52 || (ehdr->e_ident[EI_CLASS] == ELFCLASS64 && st_size < 64))
		return IS_NOT_ELF;

	bool is_x64 = false;
	if (ehdr->e_ident[EI_CLASS] == ELFCLASS64)
		is_x64 = true;

	if (ehdr->e_ident[EI_MAG0] != 0x7f)
		return IS_NOT_ELF;
	else if (ehdr->e_ident[EI_MAG1] != 'E')
		return IS_NOT_ELF;
	else if (ehdr->e_ident[EI_MAG2] != 'L')
		return IS_NOT_ELF;
	else if (ehdr->e_ident[EI_MAG3] != 'F')
		return IS_NOT_ELF;

	if (ehdr->e_type != ET_EXEC && ehdr->e_type != ET_DYN && ehdr->e_type != ET_REL)
		return IS_NOT_SUPPORTED;

	if (is_x64)
		return IS_X64;
	return IS_X32;
}
