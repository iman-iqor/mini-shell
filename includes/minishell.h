/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjbar <mbenjbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:23:31 by imiqor            #+#    #+#             */
/*   Updated: 2025/05/17 20:24:40 by mbenjbar         ###   ########.fr       */
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
	struct s_env	*prev;
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


// this one is for the type of quote, whether it is '' or "" or none
typedef enum s_quote_type
{
	NONE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}						t_quote_type;

typedef struct s_file
{
	char	*file_name;
	int		flag;
	struct s_file *next;
}	t_file;

//this is for the things that u will parse for example the argumment variables means the return of the split or the args that the user will insert
typedef struct s_list
{
	char				**argument;
	t_file				*input_file;
	t_file				*output_file;
	t_quote_type		quote_type;
	struct s_list		*next;
}						t_list;
//**************************************************************************************************************************************************** */

//this is for variables that we will need ,this way is better than declaring everytime a variable and breacking the norminette rule
typedef struct s_var
{
	int i;
	
}				t_var;


//utils
int		ft_strcmp(char *s1, char *s2); // compare two string :)
char 	*ft_strcat(char *dest,char *src);
char 	*ft_strcpy(char *dest, char *src);
int		ft_strlen(const char *s);
char	*ft_strndup(char *str, int n);
void	ft_putstr(char *text);
void	graceful_exit(void);

//execution
void	exec_builtin(t_list *list);  //here where i check the args and see if there is anything matchs a builtin function name
int	is_builtin(char *cmd);//hna rr kancompari chnu eandi mea l builtins names if true 1 sinon 0
void execone(t_list *list);//ila makanch builtin ra kanmchi n executih ela dak l assas hna
int	ft_exec_single_command(t_list *list);
void	ft_exec(t_list *list);
//heredoc
int	heredoc(t_list *list);
void	child_heredoc(char *delim);
//builtins
void	echo(char **list);   // echo builtin 
int		is_flag(char *str);   //helper for echo
//cd
void	cd_error(int code);
t_env	*get_envar(char *key);
void	cd(char **path);
int if_else_of_cd(char **path, t_env *home, char **p);
void update_pwd();
//pwd
void	pwd(void);
//env
void	env(void);
//export
t_env *last_envar(t_env *env_list);
void addback(t_env *new_node);
char **get_env_keys(t_env *env_list);
int is_valid(char *str);
t_env *get_envar_with_passing_env_list(t_env *env, char *key);
int get_key_and_value(char *str, char **key, char **value);
t_env *add_env_var(char *key, char *value, t_env *prev);
void export_logique(char **list);
void print_env_var(t_env *env);
void sort_ascii(char **arr);
void print_export_sorted(char **keys, t_env *env_list);
void export_no_args(void);
void export(char **list);
void handle_exit_status(int flag);
//unset
int is_valid_unset(char *str);
void	unset_var(char *key);
void	handle_unset_error(char *arg);
void	unset(char **list);
//exit
 int	is_numeric_argument(const char *arg);
 void	exit_error_numeric(char *arg);
 void	exit_error_too_many_args(void);
void	cleanup_and_exit(int status);
void	ft_exit(char **args);








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



// it will store value of each token itself, and pointer for the next one, and the type of it
typedef struct s_token
{
	t_token_type		type;
	char				*value;
	t_quote_type		quote_type;
	struct s_token		*next;
}						t_token;





//This the parser functions declarations

t_list    *parse_cmd(char *input, t_env *env);
t_env	*init_env(char **env);
t_token *tokenize_input(char *input);
char	*process_input(char *input, int *i, t_quote_type *quote_type);
char	*get_operator(char *input, int *i, t_quote_type *quote_type);
char	*get_word(char *input, int *i, t_quote_type *quote_type);
t_token_type	get_token_type(char *value);
char	*get_env_value(t_env *env, char *key);
void	expand_variables(t_token *tokens, t_env *env);
char	*case_of_squote(char *word, int *i, char *result);
char	*case_of_dquote(char *word, int *i, char *result, t_env *env);
char	*case_of_normal_var(char *word, int *i, char *result, t_env *env);
char	*case_of_var_with_next_char_squote(char *word, int *i, char *result);
char	*case_of_var_with_next_char_dquote(char *word, int *i, char *result);
char	*case_of_var_with_next_char_digit(char *word, int *i, char *result);
char	*case_of_var_with_exit_status(int *i, char *result);
char	*case_of_word(char *word, int *i, char *result);
char	*ft_strjoin_char(char *str, char c);
t_list	*parse_tokens(t_token *tokens);
char	**ft_realloc_array(char **arr, char *new_str);
void	free_tokens(t_token *tokens);
t_list	*ft_add_file(t_list *cmds, char *new_str, int flag, char c);
#endif

