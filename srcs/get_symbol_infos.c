#include "ft_nm.h"

Elf64_Sym_Nm *get_symbol_infos_x64(void *f, Elf64_Shdr *symtab_hdr, Elf64_Sym *symbol) {
	Elf64_Sym_Nm *new = malloc(sizeof(Elf64_Sym_Nm));
	new->symbol_name = get_symbol_name_x64(f, symtab_hdr, symbol->st_name);
	new->symbol_value = get_symbol_value_x64(symbol);
	new->symbol_type = get_symbol_type_x64(f, symbol);
	new->next = NULL;
	return new;
}

Elf32_Sym_Nm *get_symbol_infos_x32(void *f, Elf32_Shdr *symtab_hdr, Elf32_Sym *symbol) {
	Elf32_Sym_Nm *new = malloc(sizeof(Elf32_Sym_Nm));
	new->symbol_name = get_symbol_name_x32(f, symtab_hdr, symbol->st_name);
	new->symbol_value = get_symbol_value_x32(symbol);
	new->symbol_type = get_symbol_type_x32(f, symbol);
	new->next = NULL;
	return new;
}

char* get_symbol_value_x64(Elf64_Sym *sym) {
	if (sym->st_shndx == SHN_UNDEF)
		return stringdup("                ");
	char *str = malloc(128);
	*str = '\0';
	sprintfmt(str, "%0lx", sym->st_value);
	return str;
}

char* get_symbol_value_x32(Elf32_Sym *sym) {
	if (sym->st_shndx == SHN_UNDEF)
		return stringdup("                ");
	char *str = malloc(128);
	*str = '\0';
	sprintfmt(str, "%0lx", sym->st_value);
	return str;
}

char *get_symbol_name_x64(void *f, Elf64_Shdr *symtab_hdr, uint32_t st_name) {
	Elf64_Shdr *strtab_hdr = get_section_header_x64(f, symtab_hdr->sh_link);
	return f + strtab_hdr->sh_offset + st_name;
}

char *get_symbol_name_x32(void *f, Elf32_Shdr *symtab_hdr, uint32_t st_name) {
	Elf32_Shdr *strtab_hdr = get_section_header_x32(f, symtab_hdr->sh_link);
	return f + strtab_hdr->sh_offset + st_name;
}

Elf64_Sym *get_symbol_x64(void *f, Elf64_Shdr *symtab_hdr, uint32_t idx) {
	return f + (symtab_hdr->sh_offset + (idx * symtab_hdr->sh_entsize));
}

Elf32_Sym *get_symbol_x32(void *f, Elf32_Shdr *symtab_hdr, uint32_t idx) {
	return f + (symtab_hdr->sh_offset + (idx * symtab_hdr->sh_entsize));
}

char get_symbol_type_x64(void *f, Elf64_Sym *sym) {
	int bind = ELF64_ST_BIND(sym->st_info);
	int type = ELF64_ST_TYPE(sym->st_info);
	if (type == STT_FILE || type == STT_SECTION)
		return 'a';

	if (bind == STB_WEAK && sym->st_value)
		return 'W';
	else if (bind == STB_WEAK && !sym->st_value) {
		return 'w';
	}

	switch (sym->st_shndx) {
		case SHN_ABS: return 'A';
		case SHN_UNDEF: return 'U';
	}
	
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)f;
	Elf64_Shdr *shdr = get_section_header_x64(f, sym->st_shndx);
	Elf64_Shdr *shstrtb = get_section_header_x64(f, ehdr->e_shstrndx);
	char *section_name = (char *)(f + shstrtb->sh_offset + shdr->sh_name);
	(void)ehdr; (void)shdr;

	if (stringcmp(section_name, ".text") == 0 && bind == STB_GLOBAL)
		return 'T';
	else if (stringcmp(section_name, ".text") == 0 && bind == STB_LOCAL)
		return 't';
	else if (stringcmp(section_name, "completed.0") == 0 && bind == STB_GLOBAL)
		return 'B';
	else if (stringcmp(section_name, "completed.0") == 0 && bind == STB_LOCAL)
		return 'b';
	else if (stringcmp(section_name, ".fini") == 0 && bind == STB_GLOBAL)
		return 'T';
	else if (stringcmp(section_name, ".fini") == 0 && bind == STB_LOCAL)
		return 't';
	else if (stringcmp(section_name, ".data") == 0 && bind == STB_GLOBAL)
		return 'D';
	else if (stringcmp(section_name, ".data") == 0 && bind == STB_LOCAL)
		return 'd';
	else if (stringcmp(section_name, ".rodata") == 0 && bind == STB_GLOBAL)
		return 'R';
	else if (stringcmp(section_name, ".rodata") == 0 && bind == STB_LOCAL)
		return 'r';
	else if (stringcmp(section_name, ".bss") == 0 && bind == STB_GLOBAL)
		return 'B';
	else if (stringcmp(section_name, ".bss") == 0 && bind == STB_LOCAL)
		return 'b';
	else if (stringcmp(section_name, ".init") == 0 && bind == STB_GLOBAL)
		return 'T';
	else if (stringcmp(section_name, ".init") == 0 && bind == STB_LOCAL)
		return 't';
	else if (stringcmp(section_name, ".fini_array") == 0 && bind == STB_GLOBAL)
		return 'D';
	else if (stringcmp(section_name, ".fini_array") == 0 && bind == STB_LOCAL)
		return 'd';
	else if (stringcmp(section_name, ".init_array") == 0 && bind == STB_GLOBAL)
		return 'D';
	else if (stringcmp(section_name, ".init_array") == 0 && bind == STB_LOCAL)
		return 'd';
	else if (stringcmp(section_name, ".eh_frame") == 0 && bind == STB_GLOBAL)
		return 'R';
	else if (stringcmp(section_name, ".eh_frame") == 0 && bind == STB_LOCAL)
		return 'r';
	else if (stringcmp(section_name, ".dynamic") == 0 && bind == STB_GLOBAL)
		return 'D';
	else if (stringcmp(section_name, ".dynamic") == 0 && bind == STB_LOCAL)
		return 'd';
	else if (stringcmp(section_name, ".eh_frame_hdr") == 0 && bind == STB_GLOBAL)
		return 'R';
	else if (stringcmp(section_name, ".eh_frame_hdr") == 0 && bind == STB_LOCAL)
		return 'r';
	else if (stringcmp(section_name, ".got.plt") == 0 && bind == STB_GLOBAL)
		return 'D';
	else if (stringcmp(section_name, ".got.plt") == 0 && bind == STB_LOCAL)
		return 'd';
	else if (stringcmp(section_name, ".note.ABI-tag") == 0 && bind == STB_GLOBAL)
		return 'R';
	else if (stringcmp(section_name, ".note.ABI-tag") == 0 && bind == STB_LOCAL)
		return 'r';
	else if (stringcmp(section_name, ".got") == 0 && bind == STB_LOCAL)
		return 'd';
	else if (stringcmp(section_name, ".data.rel.ro") == 0 && bind == STB_LOCAL)
		return 'd';
	else if (stringcmp(section_name, ".jcr") == 0 && bind == STB_LOCAL)
		return 'd';

	// debug
	// else
	// 	printfmt(STDERR_FILENO, "section_name: %s\n", section_name);

	return '?';
}

char get_symbol_type_x32(void *f, Elf32_Sym *sym) {
	int bind = ELF32_ST_BIND(sym->st_info);
	int type = ELF32_ST_TYPE(sym->st_info);
	if (type == STT_FILE || type == STT_SECTION)
		return 'a';

	if (bind == STB_WEAK && sym->st_value)
		return 'W';
	else if (bind == STB_WEAK && !sym->st_value) {
		return 'w';
	}

	switch (sym->st_shndx) {
		case SHN_ABS: return 'A';
		case SHN_UNDEF: return 'U';
	}

	Elf32_Ehdr *ehdr = (Elf32_Ehdr *)f;
	Elf32_Shdr *shdr = get_section_header_x32(f, sym->st_shndx);
	Elf32_Shdr *shstrtb = get_section_header_x32(f, ehdr->e_shstrndx);
	char *section_name = (char *)(f + shstrtb->sh_offset + shdr->sh_name);
	(void)ehdr; (void)shdr;

	if (stringcmp(section_name, ".text") == 0 && bind == STB_GLOBAL)
		return 'T';
	else if (stringcmp(section_name, ".text") == 0 && bind == STB_LOCAL)
		return 't';
	else if (stringcmp(section_name, "completed.0") == 0 && bind == STB_GLOBAL)
		return 'B';
	else if (stringcmp(section_name, "completed.0") == 0 && bind == STB_LOCAL)
		return 'b';
	else if (stringcmp(section_name, ".fini") == 0 && bind == STB_GLOBAL)
		return 'T';
	else if (stringcmp(section_name, ".fini") == 0 && bind == STB_LOCAL)
		return 't';
	else if (stringcmp(section_name, ".data") == 0 && bind == STB_GLOBAL)
		return 'D';
	else if (stringcmp(section_name, ".data") == 0 && bind == STB_LOCAL)
		return 'd';
	else if (stringcmp(section_name, ".rodata") == 0 && bind == STB_GLOBAL)
		return 'R';
	else if (stringcmp(section_name, ".rodata") == 0 && bind == STB_LOCAL)
		return 'r';
	else if (stringcmp(section_name, ".bss") == 0 && bind == STB_GLOBAL)
		return 'B';
	else if (stringcmp(section_name, ".bss") == 0 && bind == STB_LOCAL)
		return 'b';
	else if (stringcmp(section_name, ".init") == 0 && bind == STB_GLOBAL)
		return 'T';
	else if (stringcmp(section_name, ".init") == 0 && bind == STB_LOCAL)
		return 't';
	else if (stringcmp(section_name, ".fini_array") == 0 && bind == STB_GLOBAL)
		return 'D';
	else if (stringcmp(section_name, ".fini_array") == 0 && bind == STB_LOCAL)
		return 'd';
	else if (stringcmp(section_name, ".init_array") == 0 && bind == STB_GLOBAL)
		return 'D';
	else if (stringcmp(section_name, ".init_array") == 0 && bind == STB_LOCAL)
		return 'd';
	else if (stringcmp(section_name, ".eh_frame") == 0 && bind == STB_GLOBAL)
		return 'R';
	else if (stringcmp(section_name, ".eh_frame") == 0 && bind == STB_LOCAL)
		return 'r';
	else if (stringcmp(section_name, ".dynamic") == 0 && bind == STB_GLOBAL)
		return 'D';
	else if (stringcmp(section_name, ".dynamic") == 0 && bind == STB_LOCAL)
		return 'd';
	else if (stringcmp(section_name, ".eh_frame_hdr") == 0 && bind == STB_GLOBAL)
		return 'R';
	else if (stringcmp(section_name, ".eh_frame_hdr") == 0 && bind == STB_LOCAL)
		return 'r';
	else if (stringcmp(section_name, ".got.plt") == 0 && bind == STB_GLOBAL)
		return 'D';
	else if (stringcmp(section_name, ".got.plt") == 0 && bind == STB_LOCAL)
		return 'd';
	else if (stringcmp(section_name, ".note.ABI-tag") == 0 && bind == STB_GLOBAL)
		return 'R';
	else if (stringcmp(section_name, ".note.ABI-tag") == 0 && bind == STB_LOCAL)
		return 'r';
	else if (stringcmp(section_name, ".got") == 0 && bind == STB_LOCAL)
		return 'd';
	else if (stringcmp(section_name, ".data.rel.ro") == 0 && bind == STB_LOCAL)
		return 'd';
	else if (stringcmp(section_name, ".jcr") == 0 && bind == STB_LOCAL)
		return 'd';

	// debug
	// else
	// 	printfmt(STDERR_FILENO, "section_name: %s\n", section_name);

	return '?';
}
