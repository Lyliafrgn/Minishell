# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lylfergu <lylfergu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/20 16:41:15 by vimazuro          #+#    #+#              #
#    Updated: 2025/05/13 20:48:50 by lylfergu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I -lreadline #-fsanitize=address
LDLIBS = -lreadline
SRC_DIR = .
INC_DIR = libft/include
LIBFT_DIR = libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a
HEADER = minishell.h

SRC_FILES = src/main.c src/errors.c src/free.c src/syntax_checker.c src/token_utils.c src/tokenization.c src/syntax_utils.c

OBJS = $(SRC_FILES:.c=.o)

all: libft $(NAME)

libft: 
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $(NAME) $(OBJS) $(LIBFT_LIB) -lreadline

%.o: $(SRC_DIR)/%.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libft
