#include "ft_nm.h"

void debug_elf_symtab(Elf64_Sym symtab) {
	printf("st_name: %d\n", symtab.st_name);
	printf("st_value: 0x%lx\n", symtab.st_value);
	printf("st_size: %ld\n", symtab.st_size);

	printf("st_info: ");
	switch(symtab.st_info) {
		case STT_NOTYPE:
			printf("STT_NOTYPE\n");
			break;
		case STT_OBJECT:
			printf("STT_OBJECT\n");
			break;
		case STT_FUNC:
			printf("STT_FUNC\n");
			break;
		case STT_SECTION:
			printf("STT_SECTION\n");
			break;
		case STT_FILE:
			printf("STT_FILE\n");
			break;
		case STT_LOPROC:
			printf("STT_LOPROC\n");
			break;
		case STT_HIPROC:
			printf("STT_HIPROC\n");
			break;
		//case STB_LOCAL:
		//	printf("STB_LOCAL\n");
		//	break;
		//case STB_GLOBAL:
		//	printf("STB_GLOBAL\n");
		//	break;
		//case STB_WEAK:
		//	printf("STB_WEAK\n");
		//	break;
		//case STB_LOPROC:
		//	printf("STB_LOPROC\n");
		//	break;
		//case STB_HIPROC:
		//	printf("STB_HIPROC\n");
		//	break;
		default:
			printf("not found, value : %d\n", symtab.st_info);
	}

	printf("st_other: ");
	switch(symtab.st_other) {
		case STV_DEFAULT:
			printf("STV_DEFAULT\n");
			break;
		case STV_INTERNAL:
			printf("STV_INTERNAL\n");
			break;
		case STV_HIDDEN:
			printf("STV_HIDDEN\n");
			break;
		case STV_PROTECTED:
			printf("STV_PROTECTED\n");
			break;
		default:
			printf("not found, value %d\n", symtab.st_other);
	}

	printf("st_shndx: %d\n", symtab.st_shndx);
}
