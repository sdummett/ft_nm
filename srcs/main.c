#include "ft_nm.h"

void help(char *progname, int fd) {
	printfmt(fd, "Usage: %s: [option(s)] [file(s)]\n", progname);
	printfmt(fd, "List symbols in [file(s)] (a.out by default).\n");
	printfmt(fd, "The options are: \n");
	printfmt(fd, "-a, --debug-syms       Display debugger-only symbols\n");
	printfmt(fd, "-g, --extern-only      Display only external symbols\n");
	printfmt(fd, "-p, --no-sort          Do not sort the symbols\n");
	printfmt(fd, "-r, --reverse-sort     Reverse the sense of the sort\n");
	printfmt(fd, "-u, --undefined-only   Display only undefined symbols\n");
	printfmt(fd, "-h, --help             Display this information\n");
}

int get_nb_files(int ac, char **av) {
	int count = 0;
	for (int i = 1; i < ac; i++) {
		if (av[i][0] != '\0')
			count++;
	}
	return count;
}

bool is_regular_file(struct stat *sb) {
	return ((sb->st_mode & S_IFMT) == S_IFREG);
}

void process_file(char *filename, char *opts, bool print_filename) {
	int fd = open(filename, O_RDONLY);
	if (fd == -1) {
		printerror(filename);
		return;
	}

	struct stat sb;

	if (fstat(fd, &sb) == -1) {
		printerror("fstat");
		close(fd);
		return;
	}

	if (is_regular_file(&sb) == false) {
		printfmt(STDERR_FILENO, "%s: Not a regular file\n", filename);
		close(fd);
		return;
	}

	void *f = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (f == MAP_FAILED) {
		printerror("mmap");
		close(fd);
		return;
	}


	int arch = check_elf_header((Elf64_Ehdr *)f, sb.st_size);
	if (arch == IS_NOT_SUPPORTED) {
		printfmt(STDERR_FILENO, "%s: elf type not supported\n", filename);
		munmap(f, sb.st_size);
		close(fd);
		return;
	}
	else if (arch == IS_NOT_ELF ||
		(arch == IS_X32 && !check_x32_elf((Elf32_Ehdr *)f, sb.st_size)) ||
		(arch == IS_X64 && !check_x64_elf((Elf64_Ehdr *)f, sb.st_size))) {
		printfmt(STDERR_FILENO, "%s: file format not recognized\n", filename);
		munmap(f, sb.st_size);
		close(fd);
		return;
	}

	if (print_filename)
		printfmt(STDOUT_FILENO, "\n%s:\n", filename);

	//	debug_elf_header(*ehdr);


	if (arch == IS_X64) {
		Elf64_Ehdr *ehdr = (Elf64_Ehdr *)f;
		for (int i = 0; i < ehdr->e_shnum; i++) {
			Elf64_Shdr *symtab_hdr = get_section_header_x64(f, i);
			if (symtab_hdr->sh_type == SHT_SYMTAB) {
				// debug_elf_section_header(*symtab_hdr);
				print_symtab_entries_x64(f, symtab_hdr, opts);
			}
		}
	}
	else if (arch == IS_X32) {
		Elf32_Ehdr *ehdr = (Elf32_Ehdr *)f;
		for (int i = 0; i < ehdr->e_shnum; i++) {
			Elf32_Shdr *symtab_hdr = get_section_header_x32(f, i);
			if (symtab_hdr->sh_type == SHT_SYMTAB) {
				// debug_elf_section_header(*symtab_hdr);
				print_symtab_entries_x32(f, symtab_hdr, opts);
			}
		}
	}
	munmap(f, sb.st_size);
	close(fd);
}

int main(int ac, char **av) {
	char opts = 0;
	get_opt(ac, av, &opts);

	if (is_option_set(&opts, OPTION_H)) {
		help(*av, STDOUT_FILENO);
		return 0;
	}
	if (is_option_set(&opts, OPTION_ERROR)) {
		help(*av, STDERR_FILENO);
		return 0;
	}

	int nb_files = get_nb_files(ac, av);
	if (nb_files == 0) {
		process_file("a.out", &opts, false);
		return 0;
	}

	bool print_filename = nb_files > 1 ? true : false;

	for (int i = 1; i < ac; i++) {
		if (av[i][0] == '\0')
			continue;
		process_file(av[i], &opts, print_filename);
	}

	return 0;
}
