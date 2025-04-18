NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline #-lhistory
RM  = rm -f
SRC = main.c no_int_main/src/builtins/echo.c no_int_main/src/executor/exec1.c \
no_int_main/src/utils/ft_strcmp.c  no_int_main/src/utils/count_words.c \
no_int_main/src/gc/gc.c 




all: ${NAME} 

${NAME}: ${SRC}
	make -C ./no_int_main/libft/
	${CC} ${CFLAGS}  ${SRC} ./no_int_main//libft/libft.a ${LFLAGS} -o ${NAME}

clean:
	make -C ./no_int_main/libft/ clean

fclean: clean
	${RM} $(NAME)
	make -C ./no_int_main/libft/ fclean

re: fclean all
