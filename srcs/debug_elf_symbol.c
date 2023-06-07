#include "ft_nm.h"

void debug_sh_type_sh_flags(void *f, Elf64_Sym *sym) {
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)f;
	Elf64_Shdr *shdr = (Elf64_Shdr *)(f + ehdr->e_shoff + (sym->st_shndx * ehdr->e_shentsize));
	switch(shdr->sh_type) {
		case SHT_NULL:
			printfmt(STDOUT_FILENO, "SHT_NULL     ");
			break;
		case SHT_PROGBITS:
			printfmt(STDOUT_FILENO, "SHT_PROGBITS ");
			break;
		case SHT_SYMTAB:
			printfmt(STDOUT_FILENO, "SHT_SYMTAB   ");
			break;
		case SHT_STRTAB:
			printfmt(STDOUT_FILENO, "SHT_STRTAB   ");
			break;
		case SHT_RELA:
			printfmt(STDOUT_FILENO, "SHT_RELA     ");
			break;
		case SHT_HASH:
			printfmt(STDOUT_FILENO, "SHT_HASH     ");
			break;
		case SHT_DYNAMIC:
			printfmt(STDOUT_FILENO, "SHT_DYNAMIC  ");
			break;
		case SHT_NOTE:
			printfmt(STDOUT_FILENO, "SHT_NOTE     ");
			break;
		case SHT_NOBITS:
			printfmt(STDOUT_FILENO, "SHT_NOBITS   ");
			break;
		case SHT_REL:
			printfmt(STDOUT_FILENO, "SHT_SHLIB    ");
			break;
		case SHT_DYNSYM:
			printfmt(STDOUT_FILENO, "SHT_DYNSYM   ");
			break;
		case SHT_LOPROC:
			printfmt(STDOUT_FILENO, "SHT_LOPROC   ");
			break;
		case SHT_HIPROC:
			printfmt(STDOUT_FILENO, "SHT_HIPROC   ");
			break;
		case SHT_LOUSER:
			printfmt(STDOUT_FILENO, "SHT_LOUSER   ");
			break;
		case SHT_HIUSER:
			printfmt(STDOUT_FILENO, "SHT_HIUSER   ");
			break;
		default:
			printfmt(STDOUT_FILENO, "SHT_?????_%d ", shdr->sh_type);
	}
	switch(shdr->sh_flags) {
		case SHF_WRITE:
			printfmt(STDOUT_FILENO, "SHF_WRITE     ");
			break;
		case SHF_ALLOC:
			printfmt(STDOUT_FILENO, "SHF_ALLOC     ");
			break;
		case SHF_EXECINSTR:
			printfmt(STDOUT_FILENO, "SHF_EXECINSTR ");
			break;
		case SHF_MASKPROC:
			printfmt(STDOUT_FILENO, "SHF_MASKPROC  ");
			break;
		default:
			printfmt(STDOUT_FILENO, "SHF_?????_%ld ", shdr->sh_flags);
	}
}
void debug_st_info_st_other(Elf64_Sym *sym) {
		switch(ELF64_ST_BIND(sym->st_info)) {
		case STB_LOCAL:
			printfmt(STDOUT_FILENO, "STB_LOCAL  ");
			break;
		case STB_GLOBAL:
			printfmt(STDOUT_FILENO, "STB_GLOBAL ");
			break;
		case STB_WEAK:
			printfmt(STDOUT_FILENO, "STB_WEAK   ");
			break;
		case STB_LOPROC:
			printfmt(STDOUT_FILENO, "STB_LOPROC ");
			break;
		case STB_HIPROC:
			printfmt(STDOUT_FILENO, "STB_HIPROC ");
			break;
		default:
			printfmt(STDOUT_FILENO, "STB_???_%d ", sym->st_info);
	}

	switch(ELF64_ST_TYPE(sym->st_info)) {
		case STT_NOTYPE:
			printfmt(STDOUT_FILENO, "STT_NOTYPE  ");
			break;
		case STT_OBJECT:
			printfmt(STDOUT_FILENO, "STT_OBJECT  ");
			break;
		case STT_FUNC:
			printfmt(STDOUT_FILENO, "STT_FUNC    ");
			break;
		case STT_SECTION:
			printfmt(STDOUT_FILENO, "STT_SECTION ");
			break;
		case STT_FILE:
			printfmt(STDOUT_FILENO, "STT_FILE    ");
			break;
		case STT_LOPROC:
			printfmt(STDOUT_FILENO, "STT_LOPROC  ");
			break;
		case STT_HIPROC:
			printfmt(STDOUT_FILENO, "STT_HIPROC  ");
			break;
		default:
			printfmt(STDOUT_FILENO, "STT_????_%d ", sym->st_info);
	}

	switch(ELF64_ST_VISIBILITY(sym->st_other)) {
		case STV_DEFAULT:
			printfmt(STDOUT_FILENO, "STV_DEFAULT   ");
			break;
		case STV_INTERNAL:
			printfmt(STDOUT_FILENO, "STV_INTERNAL  ");
			break;
		case STV_HIDDEN:
			printfmt(STDOUT_FILENO, "STV_HIDDEN    ");
			break;
		case STV_PROTECTED:
			printfmt(STDOUT_FILENO, "STV_PROTECTED ");
			break;
		default:
			printfmt(STDOUT_FILENO, "STV_??????_%d ", sym->st_other);
	}
}
