#include "ft_nm.h"

static char *get_symbol_name(void *f, Elf64_Shdr *symtab_hdr, uint32_t st_name);
static Elf64_Sym *get_symbol(void *f, Elf64_Shdr *symtab_hdr, uint32_t idx);
static char* get_symbol_value(Elf64_Sym *sym);
static Elf64_Sym_Nm *get_symbol_infos(void *f, Elf64_Shdr *symtab_hdr, Elf64_Sym *symbol);
static void print_undefined_only(Elf64_Sym_Nm *node);
static void print_global_only(Elf64_Sym_Nm *node);
static void print_all(Elf64_Sym_Nm *node);
static void print_without_debug(Elf64_Sym_Nm *node);

void print_symtab_entries(void *f, Elf64_Shdr * symtab_hdr, char *opts) {
	uint32_t symtab_entries_num = symtab_hdr->sh_size / symtab_hdr->sh_entsize;

	Elf64_Sym_Nm *head = NULL;
	Elf64_Sym_Nm *tmp = NULL;
	for (uint32_t i = 1; i < symtab_entries_num; i++) {
		Elf64_Sym *symbol = get_symbol(f, symtab_hdr, i);

		if (head == NULL) {
			head = get_symbol_infos(f, symtab_hdr, symbol);
			tmp = head;
		}
		else {
			tmp->next = get_symbol_infos(f, symtab_hdr, symbol);
			tmp = tmp->next;
		}

		#ifdef DEBUG
			debug_st_info_st_other(symbol);
			debug_sh_type_sh_flags(f, symbol);
		#endif
	}

	// SORT: if -p is not set -> sort alphabetically
	// SORT: if -r is set     -> reverse the sort order
	tmp = head;
	while (tmp) {
		if (is_option_set(opts, OPTION_U))
			print_undefined_only(tmp);
		else if (is_option_set(opts, OPTION_G))
			print_global_only(tmp);
		else if (is_option_set(opts, OPTION_A))
			print_all(tmp);
		else
			print_without_debug(tmp);

		head = head->next;
		free(tmp->symbol_value);
		free(tmp);
		tmp = head;
	}
}

static void print_undefined_only(Elf64_Sym_Nm *node) {
	if (node->symbol_type == 'U' || node->symbol_type == 'w')
		printfmt(STDOUT_FILENO, "%s %c %s\n", node->symbol_value, node->symbol_type, node->symbol_name);
}

static void print_global_only(Elf64_Sym_Nm *node) {
	if (isuppercase(node->symbol_type) || node->symbol_type == 'w')
		printfmt(STDOUT_FILENO, "%s %c %s\n", node->symbol_value, node->symbol_type, node->symbol_name);
}

static void print_all(Elf64_Sym_Nm *node) {
	printfmt(STDOUT_FILENO, "%s %c %s\n", node->symbol_value, node->symbol_type, node->symbol_name);
}

static void print_without_debug(Elf64_Sym_Nm *node) {
	if (node->symbol_type != 'a')
		printfmt(STDOUT_FILENO, "%s %c %s\n", node->symbol_value, node->symbol_type, node->symbol_name);
}

static Elf64_Sym_Nm *get_symbol_infos(void *f, Elf64_Shdr *symtab_hdr, Elf64_Sym *symbol) {
	Elf64_Sym_Nm *new = malloc(sizeof(Elf64_Sym_Nm));
	new->symbol_name = get_symbol_name(f, symtab_hdr, symbol->st_name);
	new->symbol_value = get_symbol_value(symbol);
	new->symbol_type = get_symbol_type(f, symbol);
	new->next = NULL;
	return new;
}

static char* get_symbol_value(Elf64_Sym *sym) {
	if (sym->st_shndx == SHN_UNDEF)
		return stringdup("                ");
	char *str = malloc(128);
	*str = '\0';
	sprintfmt(str, "%0lx", sym->st_value);
	return str;
}

static char *get_symbol_name(void *f, Elf64_Shdr *symtab_hdr, uint32_t st_name) {
	Elf64_Shdr *strtab_hdr = get_section_header(f, symtab_hdr->sh_link);
	return f + strtab_hdr->sh_offset + st_name;
}

static Elf64_Sym *get_symbol(void *f, Elf64_Shdr *symtab_hdr, uint32_t idx) {
	return f + (symtab_hdr->sh_offset + (idx * symtab_hdr->sh_entsize));
}
