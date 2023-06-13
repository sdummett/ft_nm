#include "ft_nm.h"

Elf64_Shdr *get_section_header_x64(void *f, int idx) {
	return f + (((Elf64_Ehdr *)f)->e_shoff + (idx * ((Elf64_Ehdr *)f)->e_shentsize ));
}

Elf32_Shdr *get_section_header_x32(void *f, int idx) {
	return f + (((Elf32_Ehdr *)f)->e_shoff + (idx * ((Elf32_Ehdr *)f)->e_shentsize ));
}