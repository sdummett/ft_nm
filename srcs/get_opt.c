#include "ft_nm.h"

bool is_option_set(char *options, char option_flag) {
	return (*options & option_flag) != 0;
}

static void set_options(char *options, char opt_flag) {
	*options |= opt_flag;
}

static bool is_long_opt(char *arg) {
	return (arg[0] != '\0' && arg[1] != '\0' && arg[0] == '-' && arg[1] == '-');
}

static bool is_short_opt(char *arg) {
	return (arg[0] != '\0' && arg[0] == '-');
}

// Function to retrieve the singleton instance
static Option* get_options(int *count) {
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


static void process_long_opt(char *arg, char *opts, char *progname) {
	int count;
	Option *options = get_options(&count);

	for (long i = 0; i < count; i++) {
		if (stringcmp(arg + 2, options[i].long_opt) == 0) {
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
	printfmt(STDERR_FILENO, "%s: unrecognized option '%s'\n", progname, arg);
}

static void process_short_opt(char *arg, char *opts, char *progname) {
	int count;
	Option *options = get_options(&count);

	int arg_len = stringlen(arg);
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
				printfmt(STDERR_FILENO, "%s: unrecognized option '%c'\n", progname, arg[i]);
				return;
			}
		}
	}
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
