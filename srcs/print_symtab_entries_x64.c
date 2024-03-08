#include "ft_nm.h"

static void print_undefined_only(Elf64_Sym_Nm *node);
static void print_global_only(Elf64_Sym_Nm *node);
static void print_all(Elf64_Sym_Nm *node);
static void print_without_debug(Elf64_Sym_Nm *node);
static void merge_sort(Elf64_Sym_Nm **head);
static void reverse_linked_list(Elf64_Sym_Nm** head);

int print_symtab_entries_x64(void *f, Elf64_Shdr * symtab_hdr, char *opts) {
	if (symtab_hdr->sh_entsize == 0)
		return 0;
	uint32_t symtab_entries_num = symtab_hdr->sh_size / symtab_hdr->sh_entsize;

	Elf64_Sym_Nm *head = NULL;
	Elf64_Sym_Nm *tmp = NULL;
	for (uint32_t i = 1; i < symtab_entries_num; i++) {
		Elf64_Sym *symbol = get_symbol_x64(f, symtab_hdr, i);

		if (head == NULL) {
			head = get_symbol_infos_x64(f, symtab_hdr, symbol);
			tmp = head;
		}
		else {
			tmp->next = get_symbol_infos_x64(f, symtab_hdr, symbol);
			tmp = tmp->next;
		}

		#ifdef DEBUG
			debug_st_info_st_other(symbol);
			debug_sh_type_sh_flags(f, symbol);
		#endif
	}

	// SORT: if -p is not set -> sort alphabetically
	if (is_option_set(opts, OPTION_P) == false)
		merge_sort(&head);
	// SORT: if -r is set     -> reverse the sort order
	if (is_option_set(opts, OPTION_R) && is_option_set(opts, OPTION_P) == false)
		reverse_linked_list(&head);

	tmp = head;
	int symbols_nb = 0;
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
		symbols_nb++;
	}
	return symbols_nb;
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

static int find_non_alphabet_index(const char* str) {
	const size_t len = stringlen(str);
	for (size_t i = 0; i < len; ++i) {
		if (!isalphabet(str[i])) {
			return i; // Return the index of the non-alphabet character
		}
	}
	return -1; // Return -1 if all characters are alphabets
}

static char* remove_non_alphanum(const char* str) {
	const size_t len = stringlen(str);
	char* result = (char*)malloc((len + 1) * sizeof(char));
	if (result == NULL)
		return NULL;

	size_t i, j = 0;
	for (i = 0; i < len; ++i) {
		if (isalphanum(str[i])) {
			result[j] = tolowercase(str[i]);
			++j;
		}
	}
	result[j] = '\0';

	return result;
}

static void reverse_linked_list(Elf64_Sym_Nm** head) {
    Elf64_Sym_Nm *prev = NULL;
    Elf64_Sym_Nm *current = *head;
    Elf64_Sym_Nm *next = NULL;

    while (current != NULL) {
        next = current->next;  // Store the next node
        current->next = prev;  // Reverse the link

        // Move pointers one position ahead
        prev = current;
        current = next;
    }

    *head = prev;  // Update the head to point to the new first node (last node after reversal)
}

static int strcmp_nm(const char* s1, const char* s2) {
	char* s1_modified = remove_non_alphanum(s1);
	char* s2_modified = remove_non_alphanum(s2);

	int result = stringcmp(s1_modified, s2_modified);

	free(s1_modified);
	free(s2_modified);

	if (result == 0) {
		int s1_nonalpha = find_non_alphabet_index(s1);
		int s2_nonalpha = find_non_alphabet_index(s2);
		if (s1_nonalpha <= s2_nonalpha)
			return -1;
		return 1;
	}
	return result;
}

static Elf64_Sym_Nm* merge(Elf64_Sym_Nm *list1, Elf64_Sym_Nm *list2) {
	if (list1 == NULL)
		return list2;
	if (list2 == NULL)
		return list1;

	Elf64_Sym_Nm *merged_list = NULL;
	if (strcmp_nm(list1->symbol_name, list2->symbol_name) <= 0) {
		merged_list = list1;
		merged_list->next = merge(list1->next, list2);
	} else {
		merged_list = list2;
		merged_list->next = merge(list1, list2->next);
	}

	return merged_list;
}

static void split(Elf64_Sym_Nm *head, Elf64_Sym_Nm **firstHalf, Elf64_Sym_Nm **secondHalf) {
	if (head == NULL || head->next == NULL) {
		*firstHalf = head;
		*secondHalf = NULL;
		return;
	}

	Elf64_Sym_Nm *slow = head;
	Elf64_Sym_Nm *fast = head->next;

	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	*firstHalf = head;
	*secondHalf = slow->next;
	slow->next = NULL;
}

static void merge_sort(Elf64_Sym_Nm **head) {
	if (*head == NULL || (*head)->next == NULL)
		return;

	Elf64_Sym_Nm *firstHalf;
	Elf64_Sym_Nm *secondHalf;
	split(*head, &firstHalf, &secondHalf);

	merge_sort(&firstHalf);
	merge_sort(&secondHalf);

	*head = merge(firstHalf, secondHalf);
}
