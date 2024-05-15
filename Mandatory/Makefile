NAME = pipex
CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

SRC = pipex.c error_functions.c ft_split.c utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 

%.o: %.c pipex.h
		$(CC) $(CFLAGS) -o $@ -c $<

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: clean