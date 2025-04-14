NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline -lhistory
RM  = rm -f
SRC = src/main.c src/builtins/echo.c src/executor/exec1.c src/utils/ft_strcmp.c  src/utils/count_words.c 




all: ${NAME} 

${NAME}: ${SRC}
	make -C ./libft/
	${CC} ${CFLAGS}  ${SRC} ./libft/libft.a ${LFLAGS} -o ${NAME}

clean:
	make -C ./libft/ clean

fclean: clean
	${RM} $(NAME)
	make -C ./libft/ fclean

re: fclean all
