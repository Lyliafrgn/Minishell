# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/20 16:41:15 by vimazuro          #+#    #+#              #
#    Updated: 2025/05/14 12:38:24 by vimazuro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
SRC_DIR = .
INC_DIR = libft/include
LIBFT_DIR = libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a
HEADER = minishell.h

SRC_FILES = src/main.c \
			src/builtins/ft_built_command.c \
			src/builtins/ft_echo.c src/builtins/ft_cd.c \
			src/builtins/ft_pwd.c \
			src/builtins/ft_export.c src/builtins/ft_unset.c \
			src/builtins/ft_env.c src/builtins/ft_exit.c \
			src/env/ft_init_env.c src/env/ft_print_env.c \
			src/env/ft_free_env.c src/env/ft_env_copy.c \
			src/env/ft_sort_env.c src/env/ft_update_env.c \
			src/env/ft_find_env.c src/env/ft_valid_key_env.c \
			src/env/ft_delete_env_node.c src/env/ft_get_env.c \
			src/env/ft_env_to_array.c \
			src/executor/ft_execute_command.c \
			src/executor/ft_find_full_path.c \
			src/executor/ft_free_array.c \
			src/executor/ft_child_process.c \
			src/executor/ft_count_pipes.c \
			src/executor/ft_create_pipes.c \
			src/executor/ft_create_process.c \
			src/executor/ft_execute_all.c \
			src/executor/ft_split_by_pipes.c \
			src/utils/ft_malloc_list.c 

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
