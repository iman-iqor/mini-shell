NAME = minishell
CC = gcc
# CFLAGS = -Wall -Wextra -Werro -fPIC
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3
LFLAGS = -lreadline #-lhistory
RM  = rm -f


SRC = main.c\
src/builtins/echo.c \
src/builtins/pwd.c \
src/builtins/cd.c\
src/builtins/unset.c\
src/builtins/env.c\
src/builtins/export1.c\
src/builtins/export2.c\
src/builtins/export3.c\
src/builtins/exit.c\
src/executor/exec1.c \
src/executor/heredoc.c \
src/executor/execute_command.c\
src/executor/piped_commands.c\
src/utils/ft_strcmp.c  \
src/utils/ft_putstr.c  \
src/utils/list_len.c  \
src/utils/graceful_exit.c  \
src/gc/gc.c \
src/utils/ft_strcpy.c \
src/utils/ft_strcat.c\
src/utils/ft_strndup.c \
src/env/env.c\
src/parser/expand_env.c\
src/parser/expand_1.c\
src/parser/expand_2.c\
src/parser/init_env.c\
src/parser/tokenize.c\
src/parser/tokenize_help.c\
src/parser/parse_cmd.c\
src/parser/generate_cmds.c\
src/parser/ft_realloc_array.c\
src/parser/free_tokens.c\
src/parser/t_file.c\


all: ${NAME} 

${NAME}: ${SRC}
	make -C ./libft/
	${CC} ${CFLAGS}  ${SRC}  -I./includes .//libft/libft.a ${LFLAGS} -o ${NAME}

val:${NAME}
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=ll.sup ./minishell

clean:
	make -C ./libft/ clean

fclean: clean
	${RM} $(NAME)
	make -C ./libft/ fclean

re: fclean all
'aetsssss+65dty+d6r5y2hu+dt45y2h16+rtyh16d8t41d65y1d61''65s4gdfg41ds65fg4 6d4ty 1sd6f8y 4e98y74u4aetsssss+65dty+d6r5y2hu+dt45y2h16+rtyh16d8t41d65y1d61'
'aetsssss+65dty+d6r5y2hu+dt45y2h16+rtyh16d8t41d65y1d61''65s4gdfg41ds65fg4 6d4ty 1sd6f8y 4e98y74u4aetsssss+65dty+d6r5y2hu+dt45y2h16+rtyh16d8t41d65y1d61'