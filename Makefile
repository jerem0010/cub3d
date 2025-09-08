# **************************************************************************** #
#                                  cub3D                                       #
# **************************************************************************** #

NAME    := cub3D
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -Iincludes

OS := $(shell uname -s)

# --- MiniLibX config selon l'OS ---
ifeq ($(OS),Darwin) # macOS
	MLX_DIR   := mlx
	MLX_INC   := -I$(MLX_DIR)
	MLX_FLAGS := -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else               # Linux
	MLX_DIR   := minilibx-linux
	MLX_INC   := -I$(MLX_DIR)
	MLX_FLAGS := -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
endif

# --- Sources ---
SRCS := src/main.c src/init.c src/hooks.c src/image.c src/draw.c \
        src/world.c src/player.c src/loop.c src/raycast.c

OBJS := $(SRCS:.c=.o)

CFLAGS += $(MLX_INC)

# --- Rules ---
all: $(NAME)

$(MLX_DIR)/libmlx_Linux.a:
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(MLX_DIR)/libmlx_Linux.a
	$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
