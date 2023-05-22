#ifndef FT_NM_H
#define FT_NM_H

#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <elf.h>

// tools
#include <stdio.h>

// debug_elf_header.c
void debug_elf_header(void * f);

#endif
