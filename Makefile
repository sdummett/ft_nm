# **************************************************************************** #
#       TITLE                                                                  #
# **************************************************************************** #
NAME = ft_nm

# **************************************************************************** #
#       COMMANDS                                                               #
# **************************************************************************** #
CC = cc
#RM = rm

# **************************************************************************** #
#       FLAGS                                                                  #
# **************************************************************************** #
#RMFLAGS = -rf
CFLAGS = -Wall -Wextra -Werror

# **************************************************************************** #
#       SOURCES                                                                #
# **************************************************************************** #
SRCS = srcs/main.c \
       srcs/print_symtab_entries.c \
       srcs/get_section_header.c \
	   srcs/get_symbol_type.c \
       srcs/debug_elf_header.c \
       srcs/debug_elf_section_header.c \
       srcs/debug_elf_symtab.c \
	   srcs/debug_elf_symbol.c \
	   srcs/printfmt.c \
	   srcs/itoascii.c \
	   srcs/utoascii.c \
	   srcs/utohex.c \
	   srcs/stringutils.c \

# **************************************************************************** #
#       RULES                                                                  #
# **************************************************************************** #
OBJS = $(addprefix objs/,$(SRCS:.c=.o))
OBJ_DIRS = $(sort $(dir $(OBJS)))

objs/%.o : %.c | $(OBJ_DIRS)
	$(CC) -I. -c $(CFLAGS) $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIRS):
	mkdir -p $@

all: $(NAME)

debug: CFLAGS += -g3 -DDEBUG
debug: $(NAME)

clean:
	rm -rf objs

fclean: clean
	rm -f $(NAME)

re: fclean all

# **************************************************************************** #
#       PHONY                                                                  #
# **************************************************************************** #
.PHONY: all clean fclean re test debug
