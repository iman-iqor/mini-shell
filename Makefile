NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline #-lhistory
RM  = rm -f
SRC = main.c \
no_int_main/src/builtins/echo.c \
no_int_main/src/builtins/pwd.c \
no_int_main/src/builtins/cd.c\
no_int_main/src/builtins/unset.c\
no_int_main/src/builtins/env.c\
no_int_main/src/builtins/export1.c\
no_int_main/src/builtins/export2.c\
no_int_main/src/builtins/export3.c\
no_int_main/src/builtins/exit.c\
no_int_main/src/executor/exec1.c \
no_int_main/src/utils/ft_strcmp.c  \
no_int_main/src/utils/ft_putstr.c  \
no_int_main/src/utils/graceful_exit.c  \
no_int_main/src/gc/gc.c \
no_int_main/src/utils/ft_strcpy.c \
no_int_main/src/utils/ft_strcat.c\
no_int_main/src/utils/ft_strndup.c \
no_int_main/src/env/env.c\




all: ${NAME} 

${NAME}: ${SRC}
	make -C ./no_int_main/libft/
	${CC} ${CFLAGS}  ${SRC}  -I./no_int_main/includes ./no_int_main//libft/libft.a ${LFLAGS} -o ${NAME}

clean:
	make -C ./no_int_main/libft/ clean

fclean: clean
	${RM} $(NAME)
	make -C ./no_int_main/libft/ fclean

re: fclean all
