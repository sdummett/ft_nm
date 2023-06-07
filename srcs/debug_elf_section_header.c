#include "ft_nm.h"

void debug_elf_section_header(Elf64_Shdr shdr) {
	printfmt(STDOUT_FILENO, "sh_name: %d\n", shdr.sh_name);

	printfmt(STDOUT_FILENO, "sh_type: ");
	switch(shdr.sh_type) {
		case SHT_NULL:
			printfmt(STDOUT_FILENO, "SHT_NULL\n");
			break;
		case SHT_PROGBITS:
			printfmt(STDOUT_FILENO, "SHT_PROGBITS\n");
			break;
		case SHT_SYMTAB:
			printfmt(STDOUT_FILENO, "SHT_SYMTAB\n");
			break;
		case SHT_STRTAB:
			printfmt(STDOUT_FILENO, "SHT_STRTAB\n");
			break;
		case SHT_RELA:
			printfmt(STDOUT_FILENO, "SHT_RELA\n");
			break;
		case SHT_HASH:
			printfmt(STDOUT_FILENO, "SHT_HASH\n");
			break;
		case SHT_DYNAMIC:
			printfmt(STDOUT_FILENO, "SHT_DYNAMIC\n");
			break;
		case SHT_NOTE:
			printfmt(STDOUT_FILENO, "SHT_NOTE\n");
			break;
		case SHT_NOBITS:
			printfmt(STDOUT_FILENO, "SHT_NOBITS\n");
			break;
		case SHT_REL:
			printfmt(STDOUT_FILENO, "SHT_SHLIB\n");
			break;
		case SHT_DYNSYM:
			printfmt(STDOUT_FILENO, "SHT_DYNSYM\n");
			break;
		case SHT_LOPROC:
			printfmt(STDOUT_FILENO, "SHT_LOPROC\n");
			break;
		case SHT_HIPROC:
			printfmt(STDOUT_FILENO, "SHT_HIPROC\n");
			break;
		case SHT_LOUSER:
			printfmt(STDOUT_FILENO, "SHT_LOUSER\n");
			break;
		case SHT_HIUSER:
			printfmt(STDOUT_FILENO, "SHT_HIUSER\n");
			break;
		default:
			printfmt(STDOUT_FILENO, "not found, value: %d\n", shdr.sh_type);
	}


	printfmt(STDOUT_FILENO, "sh_addr: 0x%lx\n", shdr.sh_addr);
	printfmt(STDOUT_FILENO, "sh_offset: 0x%lx (%ld bytes)\n", shdr.sh_offset, shdr.sh_offset);
	printfmt(STDOUT_FILENO, "sh_size: 0x%lx (%ld bytes)\n", shdr.sh_size, shdr.sh_size);
	printfmt(STDOUT_FILENO, "sh_entsize: 0x%lx (%ld bytes)\n", shdr.sh_entsize, shdr.sh_entsize);

	printfmt(STDOUT_FILENO, "sh_flags: ");
	switch(shdr.sh_flags) {
		case SHF_WRITE:
			printfmt(STDOUT_FILENO, "SHF_WRITE\n");
			break;
		case SHF_ALLOC:
			printfmt(STDOUT_FILENO, "SHF_ALLOC\n");
			break;
		case SHF_EXECINSTR:
			printfmt(STDOUT_FILENO, "SHF_EXECINSTR\n");
			break;
		case SHF_MASKPROC:
			printfmt(STDOUT_FILENO, "SHF_MASKPROC\n");
			break;
		default:
			printfmt(STDOUT_FILENO, "not found, value: %ld\n", shdr.sh_flags);
	}

	printfmt(STDOUT_FILENO, "sh_link: %d\n", shdr.sh_link);
	printfmt(STDOUT_FILENO, "sh_info: %d\n", shdr.sh_info);
	printfmt(STDOUT_FILENO, "sh_addralign: 0x%lx (%ld bytes)\n", shdr.sh_addralign, shdr.sh_addralign);

}
