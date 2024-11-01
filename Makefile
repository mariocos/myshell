NAME = minishell

SRC_PATH = ./srcs
OBJ_DIR = ./objs

SRCS = $(SRC_PATH)/parse/quote_parse.c \
	   $(SRC_PATH)/parse/first_parse.c \
	   $(SRC_PATH)/lib/free_utils.c \
	   $(SRC_PATH)/lib/print_utils.c \
	   $(SRC_PATH)/lib/is.c \
	   $(SRC_PATH)/lib/libft_utils.c \
	   $(SRC_PATH)/lib/safe_malloc.c \
	   $(SRC_PATH)/token/tokenizer.c \
	   $(SRC_PATH)/token/re_token_utils.c \
       $(SRC_PATH)/token/special_split.c \
	   $(SRC_PATH)/token/re_tokenize.c \
	   $(SRC_PATH)/init/envp.c \
	   $(SRC_PATH)/main.c \



OBJ = $(SRCS:$(SRC_PATH)/%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) #-lreadline

$(OBJ_DIR)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
