#include "ft_nm.h"

void debug_elf_header(Elf64_Ehdr ehdr) {
	printf("e_ident: 0x%x %c %c %c", ehdr.e_ident[EI_MAG0], ehdr.e_ident[EI_MAG1], \
			ehdr.e_ident[EI_MAG2], ehdr.e_ident[EI_MAG3]);

	switch(ehdr.e_ident[EI_CLASS]) {
		case ELFCLASSNONE:
			printf("ELFCLASSNONE ");
			break;
		case ELFCLASS32:
			printf("ELF32 ");
			break;
		case ELFCLASS64:
			printf("ELF64 ");
			break;
		default:
			printf("(ELFCLASS not found, value: %d) ", ehdr.e_ident[EI_CLASS]);
	}

	switch(ehdr.e_ident[EI_DATA]) {
		case ELFDATANONE:
			printf("ELFDATANONE ");
			break;
		case ELFDATA2LSB:
			printf("(2's complement, little endian) ");
			break;
		case ELFDATA2MSB:
			printf("(2's complement, big endian) ");
			break;
		default:
			printf("(ELDATA not found, value: %d) ", ehdr.e_ident[EI_DATA]);
	}

	switch(ehdr.e_ident[EI_VERSION]) {
		case EV_NONE:
			printf("EV_NONE ");
			break;
		case EV_CURRENT:
			printf("EV_CURRENT ");
			break;
		default:
			printf("(EI_VERSION not found, value: %d) ", ehdr.e_ident[EI_VERSION]);
	}

	switch(ehdr.e_ident[EI_OSABI]) {
		case ELFOSABI_SYSV:
			printf("ELFOSABI_SYSV ");
			break;
		case ELFOSABI_HPUX:
			printf("ELFOSABI_HPUX ");
			break;
		case ELFOSABI_NETBSD:
			printf("ELFOSABI_NETBSD ");
			break;
		case ELFOSABI_LINUX:
			printf("ELFOSABI_LINUX ");
			break;
		case ELFOSABI_SOLARIS:
			printf("ELFOSABI_SOLARIS ");
			break;
		case ELFOSABI_IRIX:
			printf("ELFOSABI_IRIX ");
			break;
		case ELFOSABI_FREEBSD:
			printf("ELFOSABI_FREEBSD ");
			break;
		case ELFOSABI_TRU64:
			printf("ELFOSABI_TRU64 ");
			break;
		case ELFOSABI_ARM:
			printf("ELFOSABI_ARM ");
			break;
		case ELFOSABI_STANDALONE:
			printf("ELFOSABI_STANDALONE ");
			break;
		default:
			printf("(OSABI not found, value: %d) ", ehdr.e_ident[EI_OSABI]);
	}

	printf("(ABIVERSION: %d) ", ehdr.e_ident[EI_ABIVERSION]);
	printf("(EI_PAD: %d) ", ehdr.e_ident[EI_PAD]);
	printf("(EI_NIDENT: %d)\n", ehdr.e_ident[EI_NIDENT]);

	printf("e_type: ");
	switch(ehdr.e_type) {
		case ET_NONE:
			printf("ET_NONE\n");
			break;
		case ET_REL:
			printf("ET_REL\n");
			break;
		case ET_EXEC:
			printf("ET_EXEC\n");
			break;
		case ET_DYN:
			printf("ET_DYN\n");
			break;
		case ET_CORE:
			printf("ET_CORE\n");
			break;
		default:
			printf("not found, value: %d\n", ehdr.e_type);
	}

	printf("e_machine: ");
	switch(ehdr.e_machine) {
		case EM_NONE:
			printf("EM_NONE\n");
			break;
		case EM_M32:
			printf("EM_M32\n");
			break;
		case EM_SPARC:
			printf("EM_SPARC\n");
			break;
		case EM_386:
			printf("EM_386\n");
			break;
		case EM_68K:
			printf("EM_68K\n");
			break;
		case EM_88K:
			printf("EM_88K\n");
			break;
		case EM_860:
			printf("EM_860\n");
			break;
		case EM_MIPS:
			printf("EM_MIPS\n");
			break;
		case EM_PARISC:
			printf("EM_PARISC\n");
			break;
		case EM_SPARC32PLUS:
			printf("EM_SPARC32PLUS\n");
			break;
		case EM_PPC:
			printf("EM_PPC\n");
			break;
		case EM_PPC64:
			printf("EM_PPC64\n");
			break;
		case EM_S390:
			printf("EM_S390\n");
			break;
		case EM_ARM:
			printf("EM_ARM\n");
			break;
		case EM_SH:
			printf("EM_SH\n");
			break;
		case EM_SPARCV9:
			printf("EM_SPARCV9\n");
			break;
		case EM_IA_64:
			printf("EM_IA_64\n");
			break;
		case EM_X86_64:
			printf("EM_X86_64\n");
			break;
		case EM_VAX:
			printf("EM_VAX\n");
			break;
		default:
			printf("not found, value: %d\n", ehdr.e_machine);
	}

	printf("e_version: ");
	if (ehdr.e_version == EV_NONE)
		printf("EV_NONE\n");
	else if (ehdr.e_version == EV_CURRENT)
		printf("EV_CURRENT\n");
	else
		printf("not found, value: %d\n", ehdr.e_version);

	printf("e_entry: 0x%lx\n", ehdr.e_entry);
	printf("e_phoff: %ld bytes\n", ehdr.e_phoff);
	printf("e_shoff: %ld bytes\n", ehdr.e_shoff);
	printf("e_flags: 0x%x\n", ehdr.e_flags);
	printf("e_ehsize: %d bytes\n", ehdr.e_ehsize);
	printf("e_phentize: %d bytes\n", ehdr.e_phentsize);
	printf("e_phnum: %d\n", ehdr.e_phnum);
	printf("e_shentsize: %d bytes\n", ehdr.e_shentsize);
	printf("e_shnum: %d\n", ehdr.e_shnum);
	printf("e_shstrndx: %d\n", ehdr.e_shstrndx);
}
