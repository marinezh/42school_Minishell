# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/10 14:19:08 by mzhivoto          #+#    #+#              #
#    Updated: 2025/04/29 11:54:48 by ikozhina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Library name
NAME = libft.a

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I../includes/

# Source files and object files
SRC = ft_bzero.c\
	ft_calloc.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_memset.c\
	ft_strchr.c\
	ft_strdup.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_strlen.c\
	ft_strncmp.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_tolower.c\
	ft_toupper.c\
	ft_atoi.c\
	ft_putchar_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_putstr_fd.c\
	ft_substr.c\
	ft_strjoin.c\
	ft_strmapi.c\
	ft_strtrim.c\
	ft_striteri.c\
	ft_itoa.c\
	ft_split.c\
	ft_putchar.c\
	ft_putstr.c\
	ft_putnbr.c\
	ft_puthex.c\
	ft_put_unsigned.c\
	ft_putptr.c\
	ft_printf.c\
	get_next_line.c\
	get_next_line_utils.c\
	ft_lstnew.c \
	ft_lstsize.c\
	ft_lstlast.c\
	ft_lstdelone.c\
	ft_lstclear.c\
	ft_lstadd_front.c\
	ft_lstadd_back.c\
	ft_strcmp.c\
	ft_strndup.c\

OBJ = $(SRC:.c=.o)

# Default rule to create the library
all: $(NAME)

# Rule to create the library from object files
$(NAME): $(OBJ)
	ar rcs $@ $^

# Compile each .c file into a .o file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove object files and the library
clean:
	rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
