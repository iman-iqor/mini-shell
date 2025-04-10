NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline -lhistory
RM  = rm -f
SRC = src/main.c




all: ${NAME} 

${NAME}: ${SRC}
	make -C ./libft/
	${CC} ${CFLAGS} ${LFLAGS} ${SRC} ./libft/libft.a -o ${NAME}

clean:
	make -C ./libft/ clean

fclean: clean
	${RM} $(NAME)
	make -C ./libft/ fclean

re: fclean all
