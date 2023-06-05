#include "ft_nm.h"
#define OPTION_A (1 << 0)
#define OPTION_G (1 << 1)
#define OPTION_P (1 << 2)
#define OPTION_R (1 << 3)
#define OPTION_U (1 << 4)
#define OPTION_H (1 << 5)
#define OPTION_ERROR (1 << 6)

// DONT FORGET STDERR WHILE PARSING OPTION
// WRITE UTILS FUNCTIONS
// - printf with some specifiers and a specific fd
// --> printf(FD, "FORMAT", va_args);
// --> specifiers: %c %s %p %d %u %x

bool is_long_opt(char *arg) {
	return (arg[0] != '\0' && arg[1] != '\0' && arg[0] == '-' && arg[1] == '-');
}
bool is_short_opt(char *arg) {
	return (arg[0] != '\0' && arg[0] == '-');
}

// Define the structure to hold the option data
typedef struct {
    const char short_opt;
    const char* long_opt;
} Option;

// Function to retrieve the singleton instance
Option* get_options(int *count) {
    static Option options[] = {
        {'a', "debug-syms"},
        {'g', "extern-only"},
		{'p', "no-sort"},
		{'r', "reverse-sort"},
		{'u', "undefined-only"},
		{'h', "help"},
    };

	if (count)
		*count = sizeof(options) / sizeof(options[0]);
    return options;
}

void set_options(char *options, char opt_flag) {
    *options |= opt_flag;
}

bool is_option_set(char *options, char option_flag) {
    return (*options & option_flag) != 0;
}

void process_long_opt(char *arg, char *opts, char *progname) {
	int count;
	Option *options = get_options(&count);

    for (long i = 0; i < count; i++) {
		if (strcmp(arg + 2, options[i].long_opt) == 0) {
			char opt_flag = 0;
			if (options[i].short_opt == 'a')
				opt_flag = OPTION_A;
			else if (options[i].short_opt == 'g')
				opt_flag = OPTION_G;
			else if (options[i].short_opt == 'p')
				opt_flag = OPTION_P;
			else if (options[i].short_opt == 'r')
				opt_flag = OPTION_R;
			else if (options[i].short_opt == 'u')
				opt_flag = OPTION_U;
			else if (options[i].short_opt == 'h')
				opt_flag = OPTION_H;
			set_options(opts, opt_flag);
			return;
		}
    }
	set_options(opts, OPTION_ERROR);
	// // stderr
	// printf("%s invalid option -- '%s'\n",progname, arg);
	printf("%s: unrecognized option '%s'\n", progname, arg);
}

void process_short_opt(char *arg, char *opts, char *progname) {
	(void)opts; (void)progname;
	int count;
	Option *options = get_options(&count);

	int arg_len = strlen(arg); //strlen is forbidden
	for (int i = 1; i < arg_len; i++) {
		for (int j = 0; j < count; j++) {
			if (arg[i] == options[j].short_opt) {
				char opt_flag = 0;
				if (options[j].short_opt == 'a')
					opt_flag = OPTION_A;
				else if (options[j].short_opt == 'g')
					opt_flag = OPTION_G;
				else if (options[j].short_opt == 'p')
					opt_flag = OPTION_P;
				else if (options[j].short_opt == 'r')
					opt_flag = OPTION_R;
				else if (options[j].short_opt == 'u')
					opt_flag = OPTION_U;
				else if (options[j].short_opt == 'h')
					opt_flag = OPTION_H;
				set_options(opts, opt_flag);
				break;
			}
			else if (j + 1 == count) {
				set_options(opts, OPTION_ERROR);
				// // stderr
				// printf("%s invalid option -- '%s'\n",progname, arg);
				printf("%s: unrecognized option '%c'\n", progname, arg[i]);
				return;
			}
		}
	}
	printf("short_opt: %s\n", arg);
}

void get_opt(int ac, char **av, char *opts) {
	// scan all arguments
	// if start with '-' or '--', process it
	// when done processing an arg, change it to NULL (to avoid consider it as a filename later)
	// option that start with '--' -> just strcmp it with known longopt
	// option that start with '-'  -> scan each characters
	// if one option is unknown, quit and print help()
	// store the options (or unknown opt) in a char using bitwise operation
	for (int i = 1; i < ac; i++){
		if (is_long_opt(*(av + i))) {
			process_long_opt(*(av + i), opts, *av);
			av[i][0] = '\0';
		}
		else if (is_short_opt(*(av + i))) {
			process_short_opt(*(av + i), opts, *av);
			av[i][0] = '\0';
		}
		if (is_option_set(opts, OPTION_ERROR))
			break;
	}
}

void help(char *progname) {
	// stderr
	printf("Usage: %s: [option(s)] [file(s)]\n", progname);
	printf("List symbols in [file(s)] (a.out by default).\n");
	printf("The options are: \n");
	printf("-a, --debug-syms       Display debugger-only symbols\n");
	printf("-g, --extern-only      Display only external symbols\n");
	printf("-p, --no-sort          Do not sort the symbols\n");
	printf("-r, --reverse-sort     Reverse the sense of the sort\n");
	printf("-u, --undefined-only   Display only undefined symbols\n");
	printf("-h, --help             Display this information\n");
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
	(void)opts;
	int fd = open(filename, O_RDONLY);
	if (fd == -1) {
		perror(filename); //perror forbidden
		return;
	}

	struct stat sb;

	if (fstat(fd, &sb) == -1) {
		perror("couldnt get file size"); // perror forbidden
		return;
	}
	//	printf("File size of '%s' is %ld bytes\n", av[1], sb.st_size);

	void *f = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	// if (f == -1) {
	//	perror("mmap");
	//	return 0;
	// }

	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)f;
	//	debug_elf_header(*ehdr);

	for (int i = 0; i < ehdr->e_shnum; i++)
	{
		Elf64_Shdr *symtab_hdr = get_section_header(f, i);
		if (symtab_hdr->sh_type == SHT_SYMTAB)
		{
			// debug_elf_section_header(*symtab_hdr);
			print_symtab_entries(f, symtab_hdr);
		}
	}
	munmap(f, sb.st_size);
	close(fd);
}

int main(int ac, char **av) {
	char opts;
	get_opt(ac, av, &opts);

	if (is_option_set(&opts, OPTION_A))
		printf("OPTION A SET\n");
	if (is_option_set(&opts, OPTION_G))
		printf("OPTION G SET\n");
	if (is_option_set(&opts, OPTION_P))
		printf("OPTION P SET\n");
	if (is_option_set(&opts, OPTION_R))
		printf("OPTION R SET\n");
	if (is_option_set(&opts, OPTION_U))
		printf("OPTION U SET\n");
	if (is_option_set(&opts, OPTION_H)) {
		printf("OPTION_H SET\n");
		help(*av);
		return 0;
	}
	if (is_option_set(&opts, OPTION_ERROR)) {
		help(*av);
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
