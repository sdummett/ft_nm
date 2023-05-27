#include "ft_nm.h"

Elf64_Shdr *get_section_header(void *f, int idx) {
	return f + (((Elf64_Ehdr *)f)->e_shoff + (idx * ((Elf64_Ehdr *)f)->e_shentsize ));
}

