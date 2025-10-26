CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = cub3d

SRCDIR = srcs
INCDIR = includes
LIBFT = libft/libft.a
GNL = gnl/gnl.a
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a
MLX_REPO = https://git.gasoff.ovh/lfirmin/mlx_42.git

# Flags pour MLX (Linux)
MLX_FLAGS = -lXext -lX11 -lm

# Couleurs
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m
BOLD = \033[1m

SRCS = \
	$(SRCDIR)/main.c \
	$(SRCDIR)/parsing/parsing.c \
	$(SRCDIR)/parsing/check_file.c \
	$(SRCDIR)/parsing/init_parsing.c \
	$(SRCDIR)/parsing/get_map.c \
	$(SRCDIR)/parsing/get_map_2.c \
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
	$(SRCDIR)/exec/loop.c \
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

# Animation de chargement
define loading_animation
	@echo "$(1)"
	@for i in 1 2 3 4 5 6 7 8 9 10; do \
		printf "$(CYAN)["; \
		for j in $$(seq 1 $$i); do printf "█"; done; \
		for j in $$(seq $$i 9); do printf " "; done; \
		printf "] $$(($$i * 10))%%$(RESET)\r"; \
		sleep 0.1; \
	done
	@echo ""
endef

all:
	@echo "$(BOLD)$(MAGENTA)"
	@echo "╔════════════════════════════════════════╗"
	@echo "║            🎮 CUB3D BUILD 🎮           ║"
	@echo "╚════════════════════════════════════════╝"
	@echo "$(RESET)"
	@$(MAKE) -s $(NAME)

$(MLX_DIR):
	@echo "$(BOLD)$(CYAN)📦 Cloning MLX42...$(RESET)"
	$(call loading_animation,$(YELLOW)⬇️  Downloading MLX42 library...)
	@if [ ! -d "$(MLX_DIR)/.git" ]; then \
		rm -rf $(MLX_DIR) > /dev/null 2>&1; \
		git clone $(MLX_REPO) $(MLX_DIR) > /dev/null 2>&1; \
	fi
	@echo "$(GREEN)✅ MLX42 cloned successfully!$(RESET)"
	@echo ""

$(MLX): $(MLX_DIR)
	@echo "$(BOLD)$(BLUE)🔨 Building MLX42...$(RESET)"
	$(call loading_animation,$(YELLOW)⚙️  Compiling MLX42...)
	@$(MAKE) -s -C $(MLX_DIR) > /dev/null 2>&1
	@echo "$(GREEN)✅ MLX42 built successfully!$(RESET)"
	@echo ""

$(LIBFT):
	@echo "$(BOLD)$(BLUE)📚 Building libft...$(RESET)"
	@$(MAKE) -s -C libft > /dev/null 2>&1 & \
	PID=$$!; \
	for i in 1 2 3 4 5 6 7 8 9 10; do \
		printf "$(CYAN)["; \
		for j in $$(seq 1 $$i); do printf "█"; done; \
		for j in $$(seq $$i 9); do printf " "; done; \
		printf "] $$(($$i * 10))%%$(RESET)\r"; \
		sleep 0.1; \
	done; \
	wait $$PID; \
	echo ""
	@echo ""

$(GNL):
	@echo "$(BOLD)$(BLUE)📚 Building gnl...$(RESET)"
	@$(MAKE) -s -C gnl > /dev/null 2>&1 & \
	PID=$$!; \
	for i in 1 2 3 4 5 6 7 8 9 10; do \
		printf "$(CYAN)["; \
		for j in $$(seq 1 $$i); do printf "█"; done; \
		for j in $$(seq $$i 9); do printf " "; done; \
		printf "] $$(($$i * 10))%%$(RESET)\r"; \
		sleep 0.1; \
	done; \
	wait $$PID; \
	echo ""
	@echo ""

$(NAME): $(MLX) $(LIBFT) $(GNL) $(SRCS) $(INCS)
	@echo "$(BOLD)$(BLUE)🎯 Building $(NAME)...$(RESET)"
	$(call loading_animation,$(YELLOW)🚀 Compiling main executable...)
	@$(CC) -g -I$(INCDIR) -I$(MLX_DIR)/include $(SRCS) -o $(NAME) $(LIBFT) $(GNL) $(MLX) $(MLX_FLAGS)
	@echo "$(BOLD)$(GREEN)"
	@echo "╔════════════════════════════════════════╗"
	@echo "║         🎉 BUILD SUCCESSFUL! 🎉        ║"
	@echo "║                                        ║"
	@echo "║     Your $(NAME) is ready to use! 🚀     ║"
	@echo "╚════════════════════════════════════════╝"
	@echo "$(RESET)"

clean:
	@echo "$(BOLD)$(YELLOW)"
	@echo "╔════════════════════════════════════════╗"
	@echo "║            🧹 CLEANING UP 🧹           ║"
	@echo "╚════════════════════════════════════════╝"
	@echo "$(RESET)"
	$(call loading_animation,$(YELLOW)🗑️  Cleaning object files...)
	@rm -f $(NAME)
	@make clean -s -C libft > /dev/null 2>&1
	@make clean -s -C gnl > /dev/null 2>&1
	@if [ -d "$(MLX_DIR)" ]; then make clean -s -C $(MLX_DIR) > /dev/null 2>&1; fi
	@echo "$(GREEN)✅ Clean completed!$(RESET)"

clean1:
	@echo "$(CYAN)🗑️  Removing executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)✅ Executable removed!$(RESET)"

fclean:
	@echo "$(BOLD)$(RED)"
	@echo "╔════════════════════════════════════════╗"
	@echo "║           💣 DEEP CLEAN 💣             ║"
	@echo "╚════════════════════════════════════════╝"
	@echo "$(RESET)"
	@$(MAKE) -s clean1
	$(call loading_animation,$(RED)🔥 Full cleanup in progress...)
	@make fclean -s -C libft > /dev/null 2>&1
	@make fclean -s -C gnl > /dev/null 2>&1
	@if [ -d "$(MLX_DIR)/minilibx-linux" ]; then make fclean -s -C $(MLX_DIR)/minilibx-linux > /dev/null 2>&1; fi
	@rm -rf $(MLX_DIR)
	@echo ""
	@echo "$(BOLD)$(GREEN)"
	@echo "╔════════════════════════════════════════╗"
	@echo "║        ✨ DEEP CLEAN COMPLETE! ✨      ║"
	@echo "║                                        ║"
	@echo "║     All files have been removed! 🗑️     ║"
	@echo "╚════════════════════════════════════════╝"
	@echo "$(RESET)"

re:
	@echo "$(BOLD)$(MAGENTA)"
	@echo "╔════════════════════════════════════════╗"
	@echo "║            🔄 REBUILDING 🔄            ║"
	@echo "╚════════════════════════════════════════╝"
	@echo "$(RESET)"
	@$(MAKE) -s fclean
	@echo ""
	@$(MAKE) -s all

.PHONY: all clean fclean re clean1