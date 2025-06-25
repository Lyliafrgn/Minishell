# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/20 16:41:15 by vimazuro          #+#    #+#              #
#    Updated: 2025/06/25 15:28:31 by vimazuro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I #-fsanitize=address
LDLIBS = -lreadline
SRC_DIR = .
INC_DIR = libft/include
LIBFT_DIR = libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a
HEADER = minishell.h

SRC_FILES = src/main.c \
			src/builtins/ft_built_command.c \
			src/builtins/ft_echo.c \
			src/builtins/ft_cd.c \
			src/builtins/ft_pwd.c \
			src/builtins/ft_export.c \
			src/builtins/ft_unset.c \
			src/builtins/ft_env.c \
			src/builtins/ft_exit.c \
			src/env/ft_init_env.c \
			src/env/ft_print_env.c \
			src/env/ft_free_env.c \
			src/env/ft_env_copy.c \
			src/env/ft_sort_env.c \
			src/env/ft_update_env.c \
			src/env/ft_find_env.c \
			src/env/ft_valid_key_env.c \
			src/env/ft_delete_env_node.c \
			src/env/ft_get_env.c \
			src/env/ft_env_to_array.c \
			src/executor/ft_execute_command.c \
			src/executor/ft_find_full_path.c \
			src/executor/ft_child_process.c \
			src/executor/ft_count.c \
			src/executor/ft_pipes_utils1.c \
			src/executor/ft_pipes_utils2.c \
			src/executor/ft_create_process.c \
			src/executor/ft_execute_all.c \
			src/executor/ft_parse_commands.c \
			src/executor/ft_handle_single_builtin.c \
			src/executor/ft_handle_single_external.c \
			src/executor/ft_handle_multiple.c \
			src/expand/expand.c \
			src/expand/expand2.c \
			src/expand/expand_utils.c \
			src/utils/ft_malloc_list.c \
			src/utils/ft_print_array.c \
			src/utils/ft_print_list.c \
			src/utils/ft_free.c \
			src/tokenization/errors.c \
			src/tokenization/syntax_checker.c \
			src/tokenization/token_utils.c \
			src/tokenization/tokenization.c \
			src/tokenization/syntax_utils.c \
			src/tokenization/syntax_utils2.c \
			src/tokenization/utils.c \
			src/redirection/ft_add_redirect.c \
			src/redirection/ft_free_redirect.c \
			src/redirection/ft_print_redirect.c \
			src/redirection/ft_apply_redirect.c \
			src/redirection/ft_tmp_utils.c \
			src/redirection/ft_redirect_utils.c \
			src/redirection/ft_heredoc_utils.c \
			src/signals/ft_signals_utils1.c \
			src/signals/ft_signals_utils2.c \

OBJS = $(SRC_FILES:.c=.o)

all: libft $(NAME)

libft: 
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $(NAME) $(OBJS) $(LIBFT_LIB) -lreadline

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libft
