#include "ft_nm.h"

char get_symbol_type(void *f, Elf64_Sym *sym) {
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
	Elf64_Shdr *shdr = get_section_header(f, sym->st_shndx);
	Elf64_Shdr *shstrtb = get_section_header(f, ehdr->e_shstrndx);
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
	
	else
		printfmt(STDERR_FILENO, "section_name: %s\n", section_name);
	
	return '?';
}