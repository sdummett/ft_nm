#include "ft_nm.h"

void debug_elf_section(Elf64_Shdr shdr) {
	printf("sh_name: %d\n", shdr.sh_name);

	printf("sh_type: ");
	switch(shdr.sh_type) {
		case SHT_NULL:
			printf("SHT_NULL\n");
			break;
		case SHT_PROGBITS:
			printf("SHT_PROGBITS\n");
			break;
		case SHT_SYMTAB:
			printf("SHT_SYMTAB\n");
			break;
		case SHT_STRTAB:
			printf("SHT_STRTAB\n");
			break;
		case SHT_RELA:
			printf("SHT_RELA\n");
			break;
		case SHT_HASH:
			printf("SHT_HASH\n");
			break;
		case SHT_DYNAMIC:
			printf("SHT_DYNAMIC\n");
			break;
		case SHT_NOTE:
			printf("SHT_NOTE\n");
			break;
		case SHT_NOBITS:
			printf("SHT_NOBITS\n");
			break;
		case SHT_REL:
			printf("SHT_SHLIB\n");
			break;
		case SHT_DYNSYM:
			printf("SHT_DYNSYM\n");
			break;
		case SHT_LOPROC:
			printf("SHT_LOPROC\n");
			break;
		case SHT_HIPROC:
			printf("SHT_HIPROC\n");
			break;
		case SHT_LOUSER:
			printf("SHT_LOUSER\n");
			break;
		case SHT_HIUSER:
			printf("SHT_HIUSER\n");
			break;
		default:
			printf("not found, value: %d\n", shdr.sh_type);
	}


	printf("sh_addr: 0%x\n", shdr.sh_addr);
	printf("sh_offset: 0x%x (%d bytes)\n", shdr.sh_offset, shdr.sh_offset);
	printf("sh_size: 0x%x (%d bytes)\n", shdr.sh_size, shdr.sh_size);
	printf("sh_entsize: 0x%x (%d bytes)\n", shdr.sh_entsize, shdr.sh_entsize);

	printf("sh_flags: ");
	switch(shdr.sh_flags) {
		case SHF_WRITE:
			printf("SHF_WRITE\n");
			break;
		case SHF_ALLOC:
			printf("SHF_ALLOC\n");
			break;
		case SHF_EXECINSTR:
			printf("SHF_EXECINSTR\n");
			break;
		case SHF_MASKPROC:
			printf("SHF_MASKPROC\n");
			break;
		default:
			printf("not found, value: %d\n", shdr.sh_flags);
	}

	printf("sh_link: %d\n", shdr.sh_link);
	printf("sh_info: %d\n", shdr.sh_info);
	printf("sh_addralign: 0x%x (%d bytes)\n", shdr.sh_addralign, shdr.sh_addralign);

}
