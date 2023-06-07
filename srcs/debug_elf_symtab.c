#include "ft_nm.h"

void debug_elf_symtab(Elf64_Sym symtab) {
	printfmt(STDOUT_FILENO, "st_name: %d\n", symtab.st_name);
	printfmt(STDOUT_FILENO, "st_value: 0x%lx\n", symtab.st_value);
	printfmt(STDOUT_FILENO, "st_size: %ld\n", symtab.st_size);

	printfmt(STDOUT_FILENO, "st_info: \n");
	switch(ELF64_ST_BIND(symtab.st_info)) {
		case STB_LOCAL:
			printfmt(STDOUT_FILENO, "STB_LOCAL\n");
			break;
		case STB_GLOBAL:
			printfmt(STDOUT_FILENO, "STB_GLOBAL\n");
			break;
		case STB_WEAK:
			printfmt(STDOUT_FILENO, "STB_WEAK\n");
			break;
		case STB_LOPROC:
			printfmt(STDOUT_FILENO, "STB_LOPROC\n");
			break;
		case STB_HIPROC:
			printfmt(STDOUT_FILENO, "STB_HIPROC\n");
			break;
		default:
			printfmt(STDOUT_FILENO, "STB not found, value : %d\n", symtab.st_info);
	}
	switch(ELF64_ST_TYPE(symtab.st_info)) {
		case STT_NOTYPE:
			printfmt(STDOUT_FILENO, "STT_NOTYPE\n");
			break;
		case STT_OBJECT:
			printfmt(STDOUT_FILENO, "STT_OBJECT\n");
			break;
		case STT_FUNC:
			printfmt(STDOUT_FILENO, "STT_FUNC\n");
			break;
		case STT_SECTION:
			printfmt(STDOUT_FILENO, "STT_SECTION\n");
			break;
		case STT_FILE:
			printfmt(STDOUT_FILENO, "STT_FILE\n");
			break;
		case STT_LOPROC:
			printfmt(STDOUT_FILENO, "STT_LOPROC\n");
			break;
		case STT_HIPROC:
			printfmt(STDOUT_FILENO, "STT_HIPROC\n");
			break;
		default:
			printfmt(STDOUT_FILENO, "STT not found, value : %d\n", symtab.st_info);
	}


	printfmt(STDOUT_FILENO, "st_other: ");
	switch(ELF64_ST_VISIBILITY(symtab.st_other)) {
		case STV_DEFAULT:
			printfmt(STDOUT_FILENO, "STV_DEFAULT\n");
			break;
		case STV_INTERNAL:
			printfmt(STDOUT_FILENO, "STV_INTERNAL\n");
			break;
		case STV_HIDDEN:
			printfmt(STDOUT_FILENO, "STV_HIDDEN\n");
			break;
		case STV_PROTECTED:
			printfmt(STDOUT_FILENO, "STV_PROTECTED\n");
			break;
		default:
			printfmt(STDOUT_FILENO, "not found, value %d\n", symtab.st_other);
	}

	printfmt(STDOUT_FILENO, "st_shndx: %d\n", symtab.st_shndx);
}
