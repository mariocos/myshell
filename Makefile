NAME = minishell

SRC_PATH = ./srcs
OBJ_DIR = ./objs

SRCS = $(SRC_PATH)/quotes/quote_parse.c \
	   $(SRC_PATH)/quotes/remove_quotes.c \
	   $(SRC_PATH)/quotes/remove_quotes_utils.c \
	   $(SRC_PATH)/input_handle/first_parse.c \
	   $(SRC_PATH)/input_handle/handle_input.c \
	   $(SRC_PATH)/lib/free_utils.c \
	   $(SRC_PATH)/lib/clean.c \
	   $(SRC_PATH)/lib/print_utils.c \
	   $(SRC_PATH)/lib/is.c \
	   $(SRC_PATH)/lib/is_2.c \
	   $(SRC_PATH)/lib/libft_utils.c \
	   $(SRC_PATH)/lib/libft_utils_2.c \
	   $(SRC_PATH)/lib/safe_malloc.c \
	   $(SRC_PATH)/lib/itoa.c \
	   $(SRC_PATH)/parse/token/tokenizer.c \
	   $(SRC_PATH)/parse/token/re_token_utils.c \
       $(SRC_PATH)/parse/token/special_split.c \
	   $(SRC_PATH)/parse/token/re_tokenize.c \
	   $(SRC_PATH)/parse/expand/hide_dolla.c \
	   $(SRC_PATH)/parse/expand/expand_utils.c \
	   $(SRC_PATH)/parse/expand/expand_var_loop.c \
	   $(SRC_PATH)/parse/expand/special_cases.c \
	   $(SRC_PATH)/parse/expand/tilde_expand.c \
	   $(SRC_PATH)/init/envp.c \
	   $(SRC_PATH)/init/mini_init.c \
	   $(SRC_PATH)/builtins/m_export.c \
	   $(SRC_PATH)/builtins/export_print.c \
	   $(SRC_PATH)/builtins/unset.c \
   	   $(SRC_PATH)/builtins/env.c \
	   $(SRC_PATH)/builtins/pwd_cd_and_echo.c \
	   $(SRC_PATH)/builtins/exit.c \
	   $(SRC_PATH)/pipex_parsing/populate_pipex.c \
	   $(SRC_PATH)/pipex_parsing/populate_pipex_utils.c \
	   $(SRC_PATH)/pipex_parsing/token_to_pipe.c \
	   $(SRC_PATH)/pipex_parsing/add_to_double_char_array.c \
	   $(SRC_PATH)/pipex/utils/twistft.c \
	   $(SRC_PATH)/pipex/utils/twistsplit.c \
	   $(SRC_PATH)/pipex/utils/pathsrch.c \
	   $(SRC_PATH)/pipex/utils/command_execution.c \
	   $(SRC_PATH)/pipex/redir/prep/prep_redir2.0.c \
	   $(SRC_PATH)/pipex/redir/prep/std_input2.0.c \
	   $(SRC_PATH)/pipex/redir/prep/doc_2.0.c \
	   $(SRC_PATH)/pipex/redir/prep/output_prep2.0.c \
	   $(SRC_PATH)/pipex/redir/prep/here_doc_helper.c \
	   $(SRC_PATH)/pipex/redir/input_redir.c \
	   $(SRC_PATH)/pipex/redir/output_redir.c \
	   $(SRC_PATH)/pipex/parent.c \
	   $(SRC_PATH)/pipex/child.c \
	   $(SRC_PATH)/pipex/parent_utils.c \
	   $(SRC_PATH)/pipex/better_wait.c \
	   $(SRC_PATH)/error_exit/error.c \
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
