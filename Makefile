CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = cub3d

SRCDIR = srcs
INCDIR = includes
LIBFT = libft/libft.a
GNL = gnl/gnl.a

SRCS = $(SRCDIR)/main.c \
	   $(SRCDIR)/parsing/parsing.c \
	   $(SRCDIR)/parsing/check_file.c \
	   $(SRCDIR)/parsing/init_parsing.c \
	   $(SRCDIR)/parsing/get_map.c \
	   $(SRCDIR)/parsing/line_detect.c \
	   $(SRCDIR)/parsing/get_textures.c \
	   $(SRCDIR)/parsing/check_colors.c \
	   $(SRCDIR)/utils/utils.c \
	   $(SRCDIR)/utils/init.c \
	   $(SRCDIR)/utils/debug.c \

INCS = $(INCDIR)/parsing.h \
	   $(INCDIR)/cub.h \
	   $(INCDIR)/messages.h \

all: $(NAME)

$(NAME): $(SRCS) $(INCS)
	@$(MAKE) -s -C libft
	@$(MAKE) -s -C gnl
	$(CC) -g -I$(INCDIR) $(SRCS) -o $(NAME) $(LIBFT) $(GNL)

clean:
	rm -f $(NAME)
	@make clean -s -C libft
	@make clean -s -C gnl

clean1:
	rm -f $(NAME)

fclean: clean1
	@make fclean -s -C libft
	@make fclean -s -C gnl
re: fclean all

.PHONY: all clean fclean re clean1
