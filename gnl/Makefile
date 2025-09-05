# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfirmin lfirmim@student.42.fr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/12 07:07:31 by lfirmin           #+#    #+#              #
#    Updated: 2024/08/12 09:15:05 by lfirmin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = gnl.a
SRCS_DIR    = srcs/
INCS_DIR    = includes/
OBJ_DIR     = obj/

SRC         = get_next_line.c get_next_line_utils.c

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDE     = -I $(INCS_DIR)
SRCS        = $(addprefix $(SRCS_DIR), $(SRC))
OBJ         = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# Colors
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
RESET       = \033[0m
WHITE       = \033[0;97m

# Loading animation
LOADING_CHARS = ⠋ ⠙ ⠹ ⠸ ⠼ ⠴ ⠦ ⠧ ⠇ ⠏

all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(YELLOW)Compiling get_next_line, Please wait...$(RESET)"
	@for char in $(LOADING_CHARS); do \
		printf "\r$(YELLOW)Compiling get_next_line, Please wait... $$char$(RESET)"; \
		sleep 0.1; \
	done
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "\r$(GREEN)fine ! $(WHITE)get_next_line compiled successfully !                 $(RESET)\n"

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@printf "$(WHITE)Clean process completed for $(GREEN)get_next_line.$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(WHITE)Full clean process completed for $(GREEN)get_next_line.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
