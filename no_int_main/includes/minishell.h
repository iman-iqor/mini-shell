/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookair <macbookair@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:23:31 by imiqor            #+#    #+#             */
/*   Updated: 2025/04/24 20:13:01 by macbookair       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <time.h>
#include "../libft/libft.h"

//garbage collector struct
typedef struct s_gc
{
	void		*ptr;
	struct s_gc	*next;
}				t_gc;


//minishell environnement struct
typedef struct s_env 
{
	char* key;
	char * value;
	struct s_env *next;
} t_env;



//general data
typedef struct s_general
{
	int					exit_status;//need to create this part
	int					i;
	int					in;
	pid_t				pid;
	int					out;
	t_env				*env_list;
	char**              env_array;
	t_gc				*garbage;
	t_gc				*files;//i need to create this part
	int					stop;
}						t_general;


extern t_general g_general;





//this is for variables that we will need ,this way is better than declaring everytime a variable and breacking the norminette rule
typedef struct s_var
{
	int i;
	
}				t_var;




//this is for the things that u will parse for example the argumment variables means the return of the split or the args that the user will insert
typedef struct s_list
{
	char				**argument; //those are the args that the user will insert for example >> " echo -n patati"
	
}						t_list;
//**************************************************************************************************************************************************** */

//utils
int		ft_strcmp(char *s1, char *s2); // compare two string :)
char 	*ft_strcat(char *dest,char *src);
char 	*ft_strcpy(char *dest, char *src);
int		ft_strlen(const char *s);
char	*ft_strndup(char *str, int n);


//builtins
void	exec_builtin(t_list *list);  //here where i check the args and see if there is anything matchs a builtin function name
void	echo(char **list);   // echo builtin 
int		is_flag(char *str);   //helper for echo
//cd
void	cd_error(int code);
t_env	*get_envar(char *key);



//env ==> my_env
t_env	*ft_create_env_node(char *env);
t_env	*init_env_list(char **env);
int	env_len(t_env *env);
char	*ft_join_key_value(char *key, char *value);
char	**env_list_to_array(t_env *env_list);

//garbage collector
void	*ft_gc(size_t n, char flag);
void	fr_ee(t_gc *gc);
t_gc	*create(void *ptr);
void	add(t_gc **gc, t_gc *new);
//************************************************* */

//after tokenizing we should know what is the type of each token we have these are the types
typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SEMICOLON,
}						t_token_type;

// this one is for the type of quote, whether it is '' or "" or none
typedef enum s_quote_type
{
	NONE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}						t_quote_type;

// it will store value of each token itself, and pointer for the next one, and the type of it
typedef struct s_token
{
	t_token_type		type;
	char				*value;
	t_quote_type		quote_type;
	struct s_token		*next;
}						t_token;

//This the parser functions declarations

void	parse_cmd(char *input);
void    init_env(char **env);
t_token *tokenize_input(char *input);
#endif

