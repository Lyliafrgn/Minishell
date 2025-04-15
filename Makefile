NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC = main.c parsing/lexer.c 
OBJ = $(SRC:.c=.o)

INCLUDES = -Iincludes

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(INCLUDES) -lreadline

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all