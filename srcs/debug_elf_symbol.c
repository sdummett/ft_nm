#include "ft_nm.h"

void debug_sh_type_sh_flags(void *f, Elf64_Sym *sym) {
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)f;
	Elf64_Shdr *shdr = (Elf64_Shdr *)(f + ehdr->e_shoff + (sym->st_shndx * ehdr->e_shentsize));
	switch(shdr->sh_type) {
		case SHT_NULL:
			printf("SHT_NULL     ");
			break;
		case SHT_PROGBITS:
			printf("SHT_PROGBITS ");
			break;
		case SHT_SYMTAB:
			printf("SHT_SYMTAB   ");
			break;
		case SHT_STRTAB:
			printf("SHT_STRTAB   ");
			break;
		case SHT_RELA:
			printf("SHT_RELA     ");
			break;
		case SHT_HASH:
			printf("SHT_HASH     ");
			break;
		case SHT_DYNAMIC:
			printf("SHT_DYNAMIC  ");
			break;
		case SHT_NOTE:
			printf("SHT_NOTE     ");
			break;
		case SHT_NOBITS:
			printf("SHT_NOBITS   ");
			break;
		case SHT_REL:
			printf("SHT_SHLIB    ");
			break;
		case SHT_DYNSYM:
			printf("SHT_DYNSYM   ");
			break;
		case SHT_LOPROC:
			printf("SHT_LOPROC   ");
			break;
		case SHT_HIPROC:
			printf("SHT_HIPROC   ");
			break;
		case SHT_LOUSER:
			printf("SHT_LOUSER   ");
			break;
		case SHT_HIUSER:
			printf("SHT_HIUSER   ");
			break;
		default:
			printf("SHT_?????_%d ", shdr->sh_type);
	}
	switch(shdr->sh_flags) {
		case SHF_WRITE:
			printf("SHF_WRITE     ");
			break;
		case SHF_ALLOC:
			printf("SHF_ALLOC     ");
			break;
		case SHF_EXECINSTR:
			printf("SHF_EXECINSTR ");
			break;
		case SHF_MASKPROC:
			printf("SHF_MASKPROC  ");
			break;
		default:
			printf("SHF_?????_%ld ", shdr->sh_flags);
	}
}
void debug_st_info_st_other(Elf64_Sym *sym) {
		switch(ELF64_ST_BIND(sym->st_info)) {
		case STB_LOCAL:
			printf("STB_LOCAL  ");
			break;
		case STB_GLOBAL:
			printf("STB_GLOBAL ");
			break;
		case STB_WEAK:
			printf("STB_WEAK   ");
			break;
		case STB_LOPROC:
			printf("STB_LOPROC ");
			break;
		case STB_HIPROC:
			printf("STB_HIPROC ");
			break;
		default:
			printf("STB_???_%d ", sym->st_info);
	}

	switch(ELF64_ST_TYPE(sym->st_info)) {
		case STT_NOTYPE:
			printf("STT_NOTYPE  ");
			break;
		case STT_OBJECT:
			printf("STT_OBJECT  ");
			break;
		case STT_FUNC:
			printf("STT_FUNC    ");
			break;
		case STT_SECTION:
			printf("STT_SECTION ");
			break;
		case STT_FILE:
			printf("STT_FILE    ");
			break;
		case STT_LOPROC:
			printf("STT_LOPROC  ");
			break;
		case STT_HIPROC:
			printf("STT_HIPROC  ");
			break;
		default:
			printf("STT_????_%d ", sym->st_info);
	}

	switch(ELF64_ST_VISIBILITY(sym->st_other)) {
		case STV_DEFAULT:
			printf("STV_DEFAULT   ");
			break;
		case STV_INTERNAL:
			printf("STV_INTERNAL  ");
			break;
		case STV_HIDDEN:
			printf("STV_HIDDEN    ");
			break;
		case STV_PROTECTED:
			printf("STV_PROTECTED ");
			break;
		default:
			printf("STV_??????_%d ", sym->st_other);
	}
}
