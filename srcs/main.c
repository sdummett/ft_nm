#include "ft_nm.h"

int main(int ac, char **av) {
	if (ac != 2) {
		printf("You must pass an executable, an object file or a library\n");
		return 0;
	}

	int fd = open(av[1], O_RDONLY);
	if (fd == -1) {
		perror(av[1]);
		return 0;
	}

	struct stat sb;

	if (fstat(fd, &sb) == -1) {
		perror("couldnt get file size");
		return 0;
	}
	printf("File size of '%s' is %d bytes\n", av[1], sb.st_size);

	void *f = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	//if (f == -1) {
	//	perror("mmap");
	//	return 0;
	//}

	Elf64_Ehdr ehdr = *(Elf64_Ehdr *)f;
	debug_elf_header(ehdr);

	Elf64_Shdr shstrtb = *(Elf64_Shdr *)(f + ehdr.e_shoff + (ehdr.e_shstrndx * ehdr.e_shentsize));
	printf(">> SHSTRTAB <<\n");
	debug_elf_section(shstrtb);
	printf(">> ======== <<\n");
	printf("//=====================================//\n");

	Elf64_Shdr symtab_hdr;
	for (int i = 0; i < 31; i++) { // 31 is an arbitrary value that match the number of shdr of this program compiled
		symtab_hdr = *(Elf64_Shdr *)(f + ehdr.e_shoff + (i * ehdr.e_shentsize));
		if (symtab_hdr.sh_type == SHT_SYMTAB) {
			printf(">>>>> SHT_SYMTAB <<<<<\n");
			printf("[%d]\n", i);
			printf("name of the section: %s\n", f + shstrtb.sh_offset + symtab_hdr.sh_name);
			//debug_elf_section(*(Elf64_Shdr *)(f + offset + (i * 64)));
			debug_elf_section(symtab_hdr);

			printf("//=====================================//\n");
			break;
		}
	}


	printf("sh_link + sh_info = %d + %d = %d\n", symtab_hdr.sh_link, symtab_hdr.sh_info, symtab_hdr.sh_link + symtab_hdr.sh_info);
	for (int i = 0; i < symtab_hdr.sh_link; i++) { // how to get the real entries num of the symtab ?
		printf(">>> SYMTAB <<<\n");
		printf("[%d]\n", i);
		Elf64_Sym symtab = *(Elf64_Sym *)(f + (symtab_hdr.sh_offset + (i * symtab_hdr.sh_entsize)));
		printf("name of the symbol: %s\n", f + 0x00005f30 + symtab.st_name);
		debug_elf_symtab(symtab);
		printf(">>>>>>><<<<<<<\n");
	}

	munmap(f, sb.st_size);
	close(fd);
	return 0;
}
