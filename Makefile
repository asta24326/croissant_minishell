NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -I includes
RL_FLAGS = -lreadline -lhistory

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

SRC_DIR = src
PRS_DIR = $(SRC_DIR)/parsing
EXEC_DIR = $(SRC_DIR)/execution
INCL_DIR = includes

SRC =	$(PRS_DIR)/main.c \
		$(PRS_DIR)/minishell_initialization.c \
		$(PRS_DIR)/signal_handling.c \
		$(PRS_DIR)/minishell_termination.c \
		$(PRS_DIR)/parsing.c \
		$(PRS_DIR)/syntax_check.c \
		$(PRS_DIR)/syntax_utils.c \
		$(PRS_DIR)/parse_pipeline.c \
		$(PRS_DIR)/parse_cmd_line.c \
		$(PRS_DIR)/create_cmd_lst.c \
		$(PRS_DIR)/prepare_args_arr.c \
		$(PRS_DIR)/prepare_redirs.c \
		$(PRS_DIR)/tokenize.c \
		$(PRS_DIR)/parse_cmd.c \
		$(PRS_DIR)/parse_redir.c \
		$(PRS_DIR)/handle_quotes.c \
		$(PRS_DIR)/check_builtin_cmds.c \
		$(PRS_DIR)/handle_redirs.c \

		$(EXEC_DIR)/
		

OBJ = $(SRC:.c=.o)

INCLUDES = -I $(INCL_DIT) -I $(LIBF_DIR)

all: $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(RL_FLAGS)

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline_suppress.supp ./$(NAME)

valchild: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes --suppressions=readline_suppress.supp ./$(NAME)

clean:
	rm -rf $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
