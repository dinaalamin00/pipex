SRC = main.c error.c utils.c 
BONUS = main_bonus.c pipex_bonus.c utils_bonus.c  free_bonus.c get_next_line_utils.c get_next_line.c
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJ = ${SRC:.c=.o}
BONOBJ = ${BONUS:.c=.o}
NAME = pipex


all: $(NAME)

$(NAME): $(OBJ)
	make all -C libft
	$(CC) $(CFLAGS) $(SRC) libft/libft.a -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@
	
bonus: $(BONOBJ)
	make all -C libft
	$(CC) $(CFLAGS) $(BONUS) libft/libft.a -o $(NAME)

clean:
	make clean -C libft
	rm -f $(OBJ) $(BONOBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

reb: fclean bonus
