# **************************************************************************** #
#       TITLE                                                                  #
# **************************************************************************** #
NAME = ft_nm
SHARED_OBJECT = ft_nm.so

# **************************************************************************** #
#       COMMANDS                                                               #
# **************************************************************************** #
CC = cc

# **************************************************************************** #
#       FLAGS                                                                  #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
ifeq ($(X32), 1)
	CFLAGS += -m32
endif

# **************************************************************************** #
#       SOURCES                                                                #
# **************************************************************************** #
SRCS = srcs/main.c \
       srcs/print_symtab_entries_x64.c \
       srcs/print_symtab_entries_x32.c \
       srcs/get_section_header.c \
	   srcs/get_symbol_infos.c \
       srcs/debug_elf_header.c \
       srcs/debug_elf_section_header.c \
       srcs/debug_elf_symtab.c \
	   srcs/debug_elf_symbol.c \
	   srcs/stringutils.c \
	   srcs/get_opt.c \
	   srcs/check_elf_format.c \

# **************************************************************************** #
#       RULES                                                                  #
# **************************************************************************** #
OBJS = $(addprefix objs/,$(SRCS:.c=.o))
OBJ_DIRS = $(sort $(dir $(OBJS)))

objs/%.o : %.c | $(OBJ_DIRS)
	$(CC) -I. -c $(CFLAGS) $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(SHARED_OBJECT):
	$(CC) $(SRCS) $(CFLAGS) -I. -fPIC -shared -o $(SHARED_OBJECT)

$(OBJ_DIRS):
	mkdir -p $@

all: $(NAME)

test:
	./test-my-nm.sh

debug: CFLAGS += -g3 -DDEBUG
debug: $(NAME)

clean:
	rm -rf objs

fclean: clean
	rm -f $(NAME) $(NAME).so

re: fclean all

# **************************************************************************** #
#       PHONY                                                                  #
# **************************************************************************** #
.PHONY: all clean fclean re test debug
