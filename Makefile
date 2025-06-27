NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror  #-fsanitize=address -g3
LFLAGS = -lreadline
RM  = rm -f


SRC = main.c\
main2.c\
src/executor/builtins/echo.c \
src/executor/builtins/pwd.c \
src/executor/builtins/cd.c\
src/executor/builtins/unset.c\
src/executor/builtins/env.c\
src/executor/builtins/export1.c\
src/executor/builtins/export2.c\
src/executor/builtins/export3.c\
src/executor/builtins/export4.c\
src/executor/builtins/exit1.c\
src/executor/builtins/exit2.c\
src/executor/check_generate_env.c \
src/executor/exec1.c \
src/executor/exec2.c \
src/executor/exec3.c \
src/executor/exec4.c \
src/executor/heredoc1.c \
src/executor/heredoc2.c \
src/executor/execute_command.c\
src/executor/execute_command2.c\
src/executor/piped_commands1.c\
src/executor/piped_commands2.c\
src/executor/piped_commands3.c\
src/utils/ft_strcmp.c  \
src/utils/ft_putstr.c  \
src/utils/list_len.c  \
src/utils/graceful_exit.c  \
src/executor/gc/gc1.c \
src/executor/gc/gc2.c \
src/utils/ft_strcpy.c \
src/utils/ft_strcat.c\
src/utils/ft_strndup.c \
src/executor/env/env.c\
src/parser/expand_env.c\
src/parser/expand_1.c\
src/parser/expand_2.c\
src/parser/tokenize.c\
src/parser/tokenize_help.c\
src/parser/parse_cmd.c\
src/parser/generate_cmds.c\
src/parser/ft_realloc_array.c\
src/parser/t_file.c\
src/parser/print_error.c\
src/parser/get_env_value.c\


all: ${NAME} 

${NAME}: ${SRC}
	make -C ./libft/
	${CC} ${CFLAGS}  ${SRC}  -I./includes ${LFLAGS} ./libft/libft.a -o ${NAME}

val:${NAME}
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=all --suppressions=ll.sup ./minishell

clean:
	make -C ./libft/ clean

fclean:
	${RM} $(NAME)
	make -C ./libft/ fclean

re: fclean all
