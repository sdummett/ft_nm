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

bool is_elf_format(Elf64_Ehdr *ehdr) {
	if (ehdr->e_ident[EI_MAG0] != 0x7f)
		return false;
	else if (ehdr->e_ident[EI_MAG1] != 'E')
		return false;
	else if (ehdr->e_ident[EI_MAG2] != 'L')
		return false;
	else if (ehdr->e_ident[EI_MAG3] != 'F')
		return false;
	return true;
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

	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)f;

	if (is_elf_format(ehdr) == false) {
		printfmt(STDERR_FILENO, "%s: file format not recognized\n", filename);
		munmap(f, sb.st_size);
		close(fd);
		return;
	}

	if (print_filename)
		printfmt(STDOUT_FILENO, "\n%s:\n", filename);

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
