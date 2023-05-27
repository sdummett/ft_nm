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
	printf("File size of '%s' is %ld bytes\n", av[1], sb.st_size);

	void *f = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	//if (f == -1) {
	//	perror("mmap");
	//	return 0;
	//}

	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)f;
	debug_elf_header(*ehdr);

	for (int i = 0; i < ehdr->e_shnum; i++) {
		Elf64_Shdr *symtab_hdr = get_section_header(f, i);
		if (symtab_hdr->sh_type == SHT_SYMTAB) {
			//debug_elf_section_header(*symtab_hdr);
			print_symtab_entries(f, symtab_hdr);
		}
	}
	munmap(f, sb.st_size);
	close(fd);
	return 0;
}

