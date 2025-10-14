# === Compiler & Flags ===
CC = gcc
CFLAGS = -fsanitize=address -g -Wall -Wextra -Werror
NAME = cub3d

# === Dossiers ===
SRCDIR = srcs
INCDIR = includes
LIBFT = libft/libft.a
GNL = gnl/gnl.a

# === Sources ===
SRCS = \
	$(SRCDIR)/main.c \
	$(SRCDIR)/parsing/parsing.c \
	$(SRCDIR)/parsing/check_file.c \
	$(SRCDIR)/parsing/init_parsing.c \
	$(SRCDIR)/parsing/get_map.c \
	$(SRCDIR)/parsing/line_detect.c \
	$(SRCDIR)/parsing/get_textures.c \
	$(SRCDIR)/parsing/check_colors.c \
	$(SRCDIR)/parsing/check_map.c \
	$(SRCDIR)/parsing/check_map_2.c \
	$(SRCDIR)/utils/init.c \
	$(SRCDIR)/utils/utils.c \
	$(SRCDIR)/exec/draw.c \
	$(SRCDIR)/exec/hooks.c \
	$(SRCDIR)/exec/image.c \
	$(SRCDIR)/exec/init.c \
	$(SRCDIR)/exec/input.c \
	$(SRCDIR)/exec/loop.c \
	$(SRCDIR)/exec/main.c \
	$(SRCDIR)/exec/player.c \
	$(SRCDIR)/exec/raycast.c \
	$(SRCDIR)/exec/textures.c \
	$(SRCDIR)/exec/world.c

# === Includes ===
INCS = \
	$(INCDIR)/parsing.h \
	$(INCDIR)/cub.h \
	$(INCDIR)/exec.h \
	$(INCDIR)/keys.h

# === Règles ===
all: $(NAME)

$(NAME): $(SRCS) $(INCS)
	@$(MAKE) -s -C libft
	@$(MAKE) -s -C gnl
	$(CC) $(CFLAGS) -I$(INCDIR) $(SRCS) -o $(NAME) $(LIBFT) $(GNL)

clean:
	rm -f $(NAME)
	@$(MAKE) -s clean -C libft
	@$(MAKE) -s clean -C gnl

fclean: clean
	@$(MAKE) -s fclean -C libft
	@$(MAKE) -s fclean -C gnl

re: fclean all

.PHONY: all clean fclean re
