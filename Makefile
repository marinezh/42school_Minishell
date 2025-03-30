# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/10 14:19:08 by mzhivoto          #+#    #+#              #
#    Updated: 2025/03/09 20:26:19 by mzhivoto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Library name
NAME = push_swap
# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes/ -g2

SRCS_PATH = ./src
OBJS_PATH = ./obj
LIBFT_PATH = ./libft

# Source files and object files
LIBFT = $(LIBFT_PATH)/libft.a
SRC = $(SRCS_PATH)/main.c \
	$(SRCS_PATH)/parse_input.c \
	$(SRCS_PATH)/check_input.c \
	$(SRCS_PATH)/helpers_function.c \
	$(SRCS_PATH)/sorting_small.c \
	$(SRCS_PATH)/sorting_large.c \
	$(SRCS_PATH)/moves_ps.c \
	$(SRCS_PATH)/moves_reverse.c \
	$(SRCS_PATH)/moves_rotate.c \
	$(SRCS_PATH)/ranking.c \
	$(SRCS_PATH)/free.c \
	$(SRCS_PATH)/chunk_utils.c \
	

OBJ := $(patsubst $(SRCS_PATH)/%.c, $(OBJS_PATH)/%.o, $(SRC))
#OBJ = $(SRCS:$(SRCS_PATH)/%.c=$(OBJS_PATH)/%.o)
#OBJ = obj/main.o obj/utils.o
#OBJ = $(SRCS:$(SRCS_PATH)/%.c=$(OBJS_PATH)/%.o)



# Default rule to create the library
all: $(NAME)

# Rule to create the library from object files
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJS_PATH):
	mkdir -p $(OBJS_PATH)

# Compile each .c file into a .o file
$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c | $(OBJS_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

# Clean rule to remove object files and the library
clean:
	@rm -rf $(OBJS_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	/bin/rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
