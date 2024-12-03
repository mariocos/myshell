NAME = minishell

SRC_PATH = ./srcs
OBJ_DIR = ./objs

SRCS = $(SRC_PATH)/quotes/quote_parse.c \
	   $(SRC_PATH)/parse/first_parse.c \
	   $(SRC_PATH)/lib/free_utils.c \
	   $(SRC_PATH)/lib/print_utils.c \
	   $(SRC_PATH)/lib/is.c \
	   $(SRC_PATH)/lib/libft_utils.c \
	   $(SRC_PATH)/lib/safe_malloc.c \
	   $(SRC_PATH)/lib/itoa.c \
	   $(SRC_PATH)/quotes/remove_quotes.c \
	   $(SRC_PATH)/token/tokenizer.c \
	   $(SRC_PATH)/token/re_token_utils.c \
       $(SRC_PATH)/token/special_split.c \
	   $(SRC_PATH)/token/re_tokenize.c \
	   $(SRC_PATH)/init/envp.c \
	   $(SRC_PATH)/init/mini_init.c \
	   $(SRC_PATH)/builtins/export.c \
	   $(SRC_PATH)/builtins/unset_and_env.c \
	   $(SRC_PATH)/builtins/pwd_cd_and_echo.c \
	   $(SRC_PATH)/builtins/exit.c \
	   $(SRC_PATH)/expand/hide_dolla.c \
	   $(SRC_PATH)/expand/expand_utils.c \
	   $(SRC_PATH)/expand/expand_var.c \
	   $(SRC_PATH)/expand/special_cases.c \
	   $(SRC_PATH)/expand/tilde_expand.c \
	   $(SRC_PATH)/input_handle/handle_input.c \
	   $(SRC_PATH)/pipex_parsing/populate_pipex.c \
	   $(SRC_PATH)/pipex_parsing/populate_pipex_utils.c \
	   $(SRC_PATH)/pipex_parsing/token_to_pipe.c \
	   $(SRC_PATH)/pipex/twistft.c \
	   $(SRC_PATH)/pipex/twistsplit.c \
	   $(SRC_PATH)/pipex/pathsrch.c \
	   $(SRC_PATH)/pipex/command_execution.c \
	   $(SRC_PATH)/pipex/parent.c \
	   $(SRC_PATH)/pipex/child.c \
	   $(SRC_PATH)/pipex/input_redir.c \
	   $(SRC_PATH)/pipex/output_redir.c \
	   $(SRC_PATH)/error_exit/error.c \
	   $(SRC_PATH)/gnl/gnl.c \
	   $(SRC_PATH)/signals/signals.c \
	   $(SRC_PATH)/main.c \

OBJ = $(SRCS:$(SRC_PATH)/%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline -lncurses

$(OBJ_DIR)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
