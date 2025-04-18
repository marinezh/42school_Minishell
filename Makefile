# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/10 14:19:08 by mzhivoto          #+#    #+#              #
#    Updated: 2025/04/17 13:36:38 by ikozhina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Library name
NAME = minishell

#Color scheme
COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_YELLOW = \033[0;33m
COLOUR_CYAN = \033[0;36m
COLOUR_END=\033[0m
COLOUR_MAGENTA = \033[0;35m
COLOUR_BRIGHT_RED = \033[1;31m
COLOUR_BRIGHT_GREEN = \033[1;32m
COLOUR_BRIGHT_YELLOW = \033[1;33m
COLOUR_BRIGHT_BLUE = \033[1;34m
COLOUR_BRIGHT_MAGENTA = \033[1;35m
COLOUR_BRIGHT_CYAN = \033[1;36m

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes/
READLINE = -lreadline

# Base Paths
SRCS_PATH = src
OBJS_PATH = obj
LIBFT_PATH = libft

#Subdirectories
BUILTINS_PATH = $(SRCS_PATH)/builtins
PARSING_PATH = $(SRCS_PATH)/parser
EXEC_PATH = $(SRCS_PATH)/exec
VPATH = $(SRCS_PATH) $(BUILTINS_PATH) $(PARSING_PATH) $(EXEC_PATH)

# Files
MAIN = main.c
BUILTINS = pwd.c
PARSING = parser.c
EXEC = exec.c

LIBFT := $(LIBFT_PATH)/libft.a

# Full paths to source files
SRC = $(addprefix $(SRCS_PATH)/, $(MAIN)) \
		$(addprefix $(BUILTINS_PATH)/, $(BUILTINS)) \
		$(addprefix $(PARSING_PATH)/, $(PARSING)) \
		$(addprefix $(EXEC_PATH)/, $(EXEC))

# Flatten object file names into obj/
OBJ := $(addprefix $(OBJS_PATH)/, $(notdir $(SRC:.c=.o)))

# Default target
all: $(NAME)

# Link the final executable
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(READLINE) -o $(NAME)
	@echo -e "$(COLOUR_BRIGHT_GREEN)$@ created$(COLOUR_END)"

# Rule to compile all .c → obj/.o
$(OBJS_PATH)/%.o: %.c | $(OBJS_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo -e "$(COLOUR_BRIGHT_BLUE)$@ created$(COLOUR_END)"

# Create obj directory
$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)
	@echo -e "$(COLOUR_BRIGHT_MAGENTA)obj directory created $(COLOUR_END)"

# Build libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH) > /dev/null 2>&1
	@echo -e "$(COLOUR_GREEN)libft library created$(COLOUR_END)"

# Cleaning rules
clean:
	@rm -rf $(OBJS_PATH) > /dev/null 2>&1
	@echo -e "$(COLOUR_BRIGHT_YELLOW)object directory cleaned$(COLOUR_END)"
	@$(MAKE) -C $(LIBFT_PATH) clean > /dev/null 2>&1
	@echo -e "$(COLOUR_BRIGHT_YELLOW)libft object files cleaned$(COLOUR_END)"

fclean: clean
	@rm -f $(NAME) > /dev/null 2>&1
	@$(MAKE) -C $(LIBFT_PATH) fclean > /dev/null 2>&1
	@echo -e "$(COLOUR_BRIGHT_RED)libft.a removed$(COLOUR_END)"
	@echo -e "$(COLOUR_BRIGHT_RED)$(NAME) removed$(COLOUR_END)"

re: fclean all

.PHONY: all clean fclean re
