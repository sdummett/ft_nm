#include "ft_nm.h"

void help(char *progname, int fd) {
	// stderr
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

void process_file(char *filename, char *opts) {
	int fd = open(filename, O_RDONLY);
	if (fd == -1) {
		printerror(filename);
		return;
	}

	struct stat sb;

	if (fstat(fd, &sb) == -1) {
		printerror("fstat");
		return;
	}

	void *f = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (f == MAP_FAILED) {
		printerror("mmap");
		return;
	}

	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)f;
	//	debug_elf_header(*ehdr);

	for (int i = 0; i < ehdr->e_shnum; i++)
	{
		Elf64_Shdr *symtab_hdr = get_section_header(f, i);
		if (symtab_hdr->sh_type == SHT_SYMTAB)
		{
			// debug_elf_section_header(*symtab_hdr);
			print_symtab_entries(f, symtab_hdr, opts);
		}
	}
	munmap(f, sb.st_size);
	close(fd);
}

int main(int ac, char **av) {
	char opts = 0;
	get_opt(ac, av, &opts);

	// if (is_option_set(&opts, OPTION_A))
	// 	printfmt(STDERR_FILENO, "OPTION A SET\n");
	// if (is_option_set(&opts, OPTION_G))
	// 	printfmt(STDERR_FILENO, "OPTION G SET\n");
	// if (is_option_set(&opts, OPTION_P))
	// 	printfmt(STDERR_FILENO, "OPTION P SET\n");
	// if (is_option_set(&opts, OPTION_R))
	// 	printfmt(STDERR_FILENO, "OPTION R SET\n");
	// if (is_option_set(&opts, OPTION_U))
	// 	printfmt(STDERR_FILENO, "OPTION U SET\n");
	if (is_option_set(&opts, OPTION_H)) {
		// printfmt(STDERR_FILENO, "OPTION_H SET\n");
		help(*av, STDOUT_FILENO);
		return 0;
	}
	if (is_option_set(&opts, OPTION_ERROR)) {
		help(*av, STDERR_FILENO);
		return 0;
	}

	int nb_files = get_nb_files(ac, av);
	if (nb_files == 0) {
		process_file("a.out", &opts);
		return 0;
	}

	for (int i = 1; i < ac; i++) {
		if (av[i][0] == '\0')
			continue;
		process_file(av[i], &opts);
	}

	return 0;
}
