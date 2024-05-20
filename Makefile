
NAME = pipex

CC = cc

CFLAGS = -g -Wall -Wextra -Werror

RM = rm -f

SRC = Mandatory/pipex.c Mandatory/utils.c Mandatory/utils_suit.c   Mandatory/error_functions.c Mandatory/ft_split.c 

SRC_BONUS = Bonus/pipex_bonus.c Bonus/utils_bonus.c Bonus/utils_bonus_suit.c \
		Bonus/error_functions_bonus.c Bonus/ft_split_bonus.c Bonus/get_next_line.c 

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 

bonus: $(OBJ_BONUS)
		$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME)_bonus

Mandatory/%.o: Mandatory/%.c Mandatory/pipex.h
		$(CC) $(CFLAGS) -o $@ -c $<

Bonus/%.o: Bonus/%.c Bonus/pipex_bonus.h
		$(CC) $(CFLAGS) -o $@ -c $<

clean:
		$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
		$(RM) $(NAME) $(NAME)_bonus

re: fclean all

.PHONY: clean