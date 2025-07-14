
NAME = minishell

COLOUR_END=\033[0m
COLOUR_BRIGHT_RED = \033[1;31m
COLOUR_BRIGHT_GREEN = \033[1;32m
COLOUR_BRIGHT_YELLOW = \033[1;33m
COLOUR_BRIGHT_BLUE = \033[1;34m
COLOUR_BRIGHT_MAGENTA = \033[1;35m

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes/
READLINE = -lreadline

SRCS_PATH = src
OBJS_PATH = obj
LIBFT_PATH = libft
INCL_PATH = includes

BUILTINS_PATH = $(SRCS_PATH)/builtins
LEXER_PATH = $(SRCS_PATH)/lexer
EXEC_PATH = $(SRCS_PATH)/exec
PARSER_PATH = $(SRCS_PATH)/parser
UTILS_PATH = $(SRCS_PATH)/utils
SIGNALS_PATH = $(SRCS_PATH)/signals
EXP_PATH = $(SRCS_PATH)/expantion
VPATH = $(SRCS_PATH) $(BUILTINS_PATH) $(LEXER_PATH) $(EXEC_PATH) $(PARSER_PATH) \
		$(UTILS_PATH) $(SIGNALS_PATH) $(EXP_PATH) $(INCL_PATH)

MAIN = main.c
HEADER_FILES = error_messages.h exec.h expantion.h lexer.h libft.h minishell.h parser.h structs.h utils.h
BUILTINS = ft_pwd.c ft_echo.c ft_env.c ft_export.c export_print.c utils_builtin.c ft_unset.c\
			ft_cd.c ft_exit.c free_utils.c
LEXER = lexer.c operator_check.c split.c utils.c
EXEC = init_data.c free_data.c execute.c utils_exec.c run_builtin.c run_external.c run_cmd.c\
		handle_errors.c process_redir.c run_heredoc_1.c run_pipes_1.c run_pipes_2.c process_cmd.c\
		run_heredoc_2.c process_exit.c
PARSER = parser.c tokenization.c error_check.c parser_handlers.c redirect.c clean_quotes.c parser_utils.c
UTILS = free.c free_2.c
SIGNALS = handler.c heredoc_handler.c
EXPANTION = expantion.c exp_utils.c exp_split.c exp_heredoc.c exp_handlers.c

LIBFT := $(LIBFT_PATH)/libft.a

SRC = $(addprefix $(SRCS_PATH)/, $(MAIN)) \
		$(addprefix $(BUILTINS_PATH)/, $(BUILTINS)) \
		$(addprefix $(LEXER_PATH)/, $(LEXER)) \
		$(addprefix $(EXEC_PATH)/, $(EXEC)) \
		$(addprefix $(PARSER_PATH)/, $(PARSER)) \
		$(addprefix $(UTILS_PATH)/, $(UTILS)) \
		$(addprefix $(SIGNALS_PATH)/, $(SIGNALS)) \
		$(addprefix $(EXP_PATH)/, $(EXPANTION)) \

OBJ := $(addprefix $(OBJS_PATH)/, $(notdir $(SRC:.c=.o)))

HEADERS = $(addprefix $(INCL_PATH)/, $(HEADER_FILES))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(READLINE) -o $(NAME)
	@echo -e "$(COLOUR_BRIGHT_GREEN)$@ created$(COLOUR_END)"

$(OBJS_PATH)/%.o: %.c $(HEADERS) | $(OBJS_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo -e "$(COLOUR_BRIGHT_BLUE)$@ created$(COLOUR_END)"

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)
	@echo -e "$(COLOUR_BRIGHT_MAGENTA)obj directory created $(COLOUR_END)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH) > /dev/null 2>&1
	@echo -e "$(COLOUR_BRIGHT_GREEN)libft library created$(COLOUR_END)"

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
