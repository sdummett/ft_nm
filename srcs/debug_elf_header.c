#include "ft_nm.h"

void debug_elf_header(Elf64_Ehdr ehdr) {
	printfmt(STDOUT_FILENO, "e_ident: 0x%x %c %c %c", ehdr.e_ident[EI_MAG0], ehdr.e_ident[EI_MAG1], \
			ehdr.e_ident[EI_MAG2], ehdr.e_ident[EI_MAG3]);

	switch(ehdr.e_ident[EI_CLASS]) {
		case ELFCLASSNONE:
			printfmt(STDOUT_FILENO, "ELFCLASSNONE ");
			break;
		case ELFCLASS32:
			printfmt(STDOUT_FILENO, "ELF32 ");
			break;
		case ELFCLASS64:
			printfmt(STDOUT_FILENO, "ELF64 ");
			break;
		default:
			printfmt(STDOUT_FILENO, "(ELFCLASS not found, value: %d) ", ehdr.e_ident[EI_CLASS]);
	}

	switch(ehdr.e_ident[EI_DATA]) {
		case ELFDATANONE:
			printfmt(STDOUT_FILENO, "ELFDATANONE ");
			break;
		case ELFDATA2LSB:
			printfmt(STDOUT_FILENO, "(2's complement, little endian) ");
			break;
		case ELFDATA2MSB:
			printfmt(STDOUT_FILENO, "(2's complement, big endian) ");
			break;
		default:
			printfmt(STDOUT_FILENO, "(ELDATA not found, value: %d) ", ehdr.e_ident[EI_DATA]);
	}

	switch(ehdr.e_ident[EI_VERSION]) {
		case EV_NONE:
			printfmt(STDOUT_FILENO, "EV_NONE ");
			break;
		case EV_CURRENT:
			printfmt(STDOUT_FILENO, "EV_CURRENT ");
			break;
		default:
			printfmt(STDOUT_FILENO, "(EI_VERSION not found, value: %d) ", ehdr.e_ident[EI_VERSION]);
	}

	switch(ehdr.e_ident[EI_OSABI]) {
		case ELFOSABI_SYSV:
			printfmt(STDOUT_FILENO, "ELFOSABI_SYSV ");
			break;
		case ELFOSABI_HPUX:
			printfmt(STDOUT_FILENO, "ELFOSABI_HPUX ");
			break;
		case ELFOSABI_NETBSD:
			printfmt(STDOUT_FILENO, "ELFOSABI_NETBSD ");
			break;
		case ELFOSABI_LINUX:
			printfmt(STDOUT_FILENO, "ELFOSABI_LINUX ");
			break;
		case ELFOSABI_SOLARIS:
			printfmt(STDOUT_FILENO, "ELFOSABI_SOLARIS ");
			break;
		case ELFOSABI_IRIX:
			printfmt(STDOUT_FILENO, "ELFOSABI_IRIX ");
			break;
		case ELFOSABI_FREEBSD:
			printfmt(STDOUT_FILENO, "ELFOSABI_FREEBSD ");
			break;
		case ELFOSABI_TRU64:
			printfmt(STDOUT_FILENO, "ELFOSABI_TRU64 ");
			break;
		case ELFOSABI_ARM:
			printfmt(STDOUT_FILENO, "ELFOSABI_ARM ");
			break;
		case ELFOSABI_STANDALONE:
			printfmt(STDOUT_FILENO, "ELFOSABI_STANDALONE ");
			break;
		default:
			printfmt(STDOUT_FILENO, "(OSABI not found, value: %d) ", ehdr.e_ident[EI_OSABI]);
	}

	printfmt(STDOUT_FILENO, "(ABIVERSION: %d) ", ehdr.e_ident[EI_ABIVERSION]);
	printfmt(STDOUT_FILENO, "(EI_PAD: %d) ", ehdr.e_ident[EI_PAD]);
	printfmt(STDOUT_FILENO, "(EI_NIDENT: %d)\n", ehdr.e_ident[EI_NIDENT]);

	printfmt(STDOUT_FILENO, "e_type: ");
	switch(ehdr.e_type) {
		case ET_NONE:
			printfmt(STDOUT_FILENO, "ET_NONE\n");
			break;
		case ET_REL:
			printfmt(STDOUT_FILENO, "ET_REL\n");
			break;
		case ET_EXEC:
			printfmt(STDOUT_FILENO, "ET_EXEC\n");
			break;
		case ET_DYN:
			printfmt(STDOUT_FILENO, "ET_DYN\n");
			break;
		case ET_CORE:
			printfmt(STDOUT_FILENO, "ET_CORE\n");
			break;
		default:
			printfmt(STDOUT_FILENO, "not found, value: %d\n", ehdr.e_type);
	}

	printfmt(STDOUT_FILENO, "e_machine: ");
	switch(ehdr.e_machine) {
		case EM_NONE:
			printfmt(STDOUT_FILENO, "EM_NONE\n");
			break;
		case EM_M32:
			printfmt(STDOUT_FILENO, "EM_M32\n");
			break;
		case EM_SPARC:
			printfmt(STDOUT_FILENO, "EM_SPARC\n");
			break;
		case EM_386:
			printfmt(STDOUT_FILENO, "EM_386\n");
			break;
		case EM_68K:
			printfmt(STDOUT_FILENO, "EM_68K\n");
			break;
		case EM_88K:
			printfmt(STDOUT_FILENO, "EM_88K\n");
			break;
		case EM_860:
			printfmt(STDOUT_FILENO, "EM_860\n");
			break;
		case EM_MIPS:
			printfmt(STDOUT_FILENO, "EM_MIPS\n");
			break;
		case EM_PARISC:
			printfmt(STDOUT_FILENO, "EM_PARISC\n");
			break;
		case EM_SPARC32PLUS:
			printfmt(STDOUT_FILENO, "EM_SPARC32PLUS\n");
			break;
		case EM_PPC:
			printfmt(STDOUT_FILENO, "EM_PPC\n");
			break;
		case EM_PPC64:
			printfmt(STDOUT_FILENO, "EM_PPC64\n");
			break;
		case EM_S390:
			printfmt(STDOUT_FILENO, "EM_S390\n");
			break;
		case EM_ARM:
			printfmt(STDOUT_FILENO, "EM_ARM\n");
			break;
		case EM_SH:
			printfmt(STDOUT_FILENO, "EM_SH\n");
			break;
		case EM_SPARCV9:
			printfmt(STDOUT_FILENO, "EM_SPARCV9\n");
			break;
		case EM_IA_64:
			printfmt(STDOUT_FILENO, "EM_IA_64\n");
			break;
		case EM_X86_64:
			printfmt(STDOUT_FILENO, "EM_X86_64\n");
			break;
		case EM_VAX:
			printfmt(STDOUT_FILENO, "EM_VAX\n");
			break;
		default:
			printfmt(STDOUT_FILENO, "not found, value: %d\n", ehdr.e_machine);
	}

	printfmt(STDOUT_FILENO, "e_version: ");
	if (ehdr.e_version == EV_NONE)
		printfmt(STDOUT_FILENO, "EV_NONE\n");
	else if (ehdr.e_version == EV_CURRENT)
		printfmt(STDOUT_FILENO, "EV_CURRENT\n");
	else
		printfmt(STDOUT_FILENO, "not found, value: %d\n", ehdr.e_version);

	printfmt(STDOUT_FILENO, "e_entry: 0x%lx\n", ehdr.e_entry);
	printfmt(STDOUT_FILENO, "e_phoff: %ld bytes\n", ehdr.e_phoff);
	printfmt(STDOUT_FILENO, "e_shoff: %ld bytes\n", ehdr.e_shoff);
	printfmt(STDOUT_FILENO, "e_flags: 0x%x\n", ehdr.e_flags);
	printfmt(STDOUT_FILENO, "e_ehsize: %d bytes\n", ehdr.e_ehsize);
	printfmt(STDOUT_FILENO, "e_phentize: %d bytes\n", ehdr.e_phentsize);
	printfmt(STDOUT_FILENO, "e_phnum: %d\n", ehdr.e_phnum);
	printfmt(STDOUT_FILENO, "e_shentsize: %d bytes\n", ehdr.e_shentsize);
	printfmt(STDOUT_FILENO, "e_shnum: %d\n", ehdr.e_shnum);
	printfmt(STDOUT_FILENO, "e_shstrndx: %d\n", ehdr.e_shstrndx);
}
