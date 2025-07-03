
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

# Valgrind config
VALGRIND = valgrind --show-leak-kinds=all --leak-check=full --track-fds=yes --log-file=valg.log \
			--suppressions=valgrind.supp --trace-children=yes

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wunused -I./includes/
# Check if we're on macOS and add readline paths
ifeq ($(shell uname), Darwin)
    # For Apple Silicon (arm64)
    ifeq ($(shell uname -m), arm64)
        READLINE_PATH = /opt/homebrew/opt/readline
    else
        # For Intel Macs (x86_64)
        READLINE_PATH = /usr/local/opt/readline
    endif
    CFLAGS += -I$(READLINE_PATH)/include
    READLINE = -L$(READLINE_PATH)/lib -lreadline
else
    READLINE = -lreadline
endif
# READLINE = -lreadline

# Base Paths
SRCS_PATH = src
OBJS_PATH = obj
LIBFT_PATH = libft

#Subdirectories
BUILTINS_PATH = $(SRCS_PATH)/builtins
LEXER_PATH = $(SRCS_PATH)/lexer
EXEC_PATH = $(SRCS_PATH)/exec
PARSER_PATH = $(SRCS_PATH)/parser
UTILS_PATH = $(SRCS_PATH)/utils
SIGNALS_PATH = $(SRCS_PATH)/signals
EXP_PATH = $(SRCS_PATH)/expantion
VPATH = $(SRCS_PATH) $(BUILTINS_PATH) $(LEXER_PATH) $(EXEC_PATH) $(PARSER_PATH) \
		$(UTILS_PATH) $(SIGNALS_PATH) $(EXP_PATH)

# Files
MAIN = main.c
BUILTINS = ft_pwd.c ft_echo.c ft_env.c ft_export.c export_print.c utils_builtin.c ft_unset.c\
			ft_cd.c ft_exit.c
LEXER = lexer.c operator_check.c split.c utils.c
EXEC = init_data.c free_data.c execute.c utils_exec.c run_builtin.c run_external.c run_cmd.c\
		handle_errors.c process_redir.c run_heredoc.c run_pipes_1.c run_pipes_2.c process_cmd.c
PARSER = parser.c tokenization.c print_delete.c error_check.c token_handlers.c redirect.c clean_quotes.c
UTILS = free.c
SIGNALS = handler.c
EXPANTION = expantion.c exp_utils.c exp_split.c exp_heredoc.c

LIBFT := $(LIBFT_PATH)/libft.a

# Full paths to source files
SRC = $(addprefix $(SRCS_PATH)/, $(MAIN)) \
		$(addprefix $(BUILTINS_PATH)/, $(BUILTINS)) \
		$(addprefix $(LEXER_PATH)/, $(LEXER)) \
		$(addprefix $(EXEC_PATH)/, $(EXEC)) \
		$(addprefix $(PARSER_PATH)/, $(PARSER)) \
		$(addprefix $(UTILS_PATH)/, $(UTILS)) \
		$(addprefix $(SIGNALS_PATH)/, $(SIGNALS)) \
		$(addprefix $(EXP_PATH)/, $(EXPANTION)) \

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
	@echo -e "$(COLOUR_BRIGHT_GREEN)libft library created$(COLOUR_END)"

# Run with Valgrind
valg: $(NAME)
	@echo -e "$(COLOUR_BRIGHT_CYAN)Running $(NAME) with Valgrind...$(COLOUR_END)"
	@$(VALGRIND) ./$(NAME)

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
