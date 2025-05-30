/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:23:31 by imiqor            #+#    #+#             */
/*   Updated: 2025/05/30 18:57:13 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>
#include <errno.h>



/*           #GARBAGE COLLECTER LIST#                      */
typedef enum e_gc_type {
    GC_MEMORY,
    GC_TEMPFILE
} t_gc_type;

typedef struct s_gc {
    void *ptr;
    t_gc_type type;  // Add this field to distinguish types
    struct s_gc *next;
} t_gc;

/*            #ENVIRONNEMENT#                                            */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

/*B               #GENERAL DATA                                     */
typedef struct s_general
{
	int exit_status; // need to create this part
	int				i;
	int				in;
	pid_t			pid;
	char *old_pwd;
	int				out;
	t_env			*env_list;
	char			**env_array;
	t_gc			*garbage;
	t_gc *files; // i need to create this part
	int				stop;
}					t_general;

extern t_general	g_general;

/*              #FILES#                      */
typedef struct s_file
{
	char			*file_name;
	int				flag;
	struct s_file	*next;
}					t_file;

/*                   #T_LIST LIST#                        */
typedef enum s_quote_type
{
	NONE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}					t_quote_type;
typedef struct s_list
{
	char			**argument;
	t_file			*input_file;
	t_file			*output_file;
	t_quote_type	quote_type;
	int				fd;
	int error_flag;
	struct s_list	*next;
}					t_list;
//**************************************************************************************************************************************************** */

typedef struct s_exec_data
{
	int		i;
	int		n_cmd;
	int		prev_fd;
	int		pipe_fd[2];
	pid_t	*pid;
}	t_exec_data;
/******************************************************************************************************************************************************* */
//                          #UTILS#
int					ft_strcmp(char *s1, char *s2);
char				*ft_strcat(char *dest, char *src);
char				*ft_strcpy(char *dest, char *src);
int					ft_strlen(const char *s);
char				*ft_strndup(char *str, int n);
void				ft_putstr(char *text);
void				graceful_exit(void);
int list_len(t_list *list);
/***************************************************************************************************************************************************************** */
//                        #EXECUTION#
void exec_builtin(t_list *list);
int	is_builtin(char *cmd);
void	input_no_output(t_list *list);
void	output_no_input(t_list *list);
void	input_output(t_list *list);
void	wait_and_update_status(pid_t pid);
void exec_externals(t_list *list);
void	ft_redirect_and_execute(t_list *list);
// heredoc
int					heredoc(t_list *list,t_file *tmp);
int					do_heredoc(t_file *tmp);
char				*get_tmp_file(void);
void				handle_heredoc_signals(void);
void				sigint_handler(int sig);
void	execute_builtins_and_externals(t_list *list);
int	ft_exec_single_command(t_list *list);
void	ft_exec(t_list *list);
//execute command
int	execute_command(t_list *list);
char	*check_path(char **env, t_list *list);
int	ft_execve(char *exact_path, t_list *list);
char	**extract_path(char **env);
char	*concatenate_path(char *dir, char *cmd);
//piped commands
void	ft_exec_piped_commands(t_list *list);
void	init_exec_data(t_exec_data *d,t_list *list);
void	handle_child_process(t_list *list, t_exec_data *d);
void	close_unused_fds(t_exec_data *d);
void	handle_parent_process(t_exec_data *d, t_list *list);
void	wait_for_all(pid_t *pid, int n);
// signals
void				h(int sig);
void	set_signals_parent(void);
void	set_signals_child(void);
// builtins
void				echo(char **list);
int					is_flag(char *str);
void				cd_error(int code);
t_env				*get_envar(char *key);
void				cd(char **path);
int					if_else_of_cd(char **path, t_env *home, char **p);
void				update_pwd(void);
void				pwd(void);
void				env(void);
t_env				*last_envar(t_env *env_list);
void				addback(t_env *new_node);
char				**get_env_keys(t_env *env_list);
int					is_valid(char *str);
t_env				*get_envar_with_passing_env_list(t_env *env, char *key);
int					get_key_and_value(char *str, char **key, char **value);
t_env				*add_env_var(char *key, char *value, t_env *prev);
void				export_logique(char **list);
void				print_env_var(t_env *env);
void				sort_ascii(char **arr);
void				print_export_sorted(char **keys, t_env *env_list);
void				export_no_args(void);
void				export(char **list);
void				handle_exit_status(int flag);
int					is_valid_unset(char *str);
void				unset_var(char *key);
void				handle_unset_error(char *arg);
void				unset(char **list);
int					is_numeric_argument(const char *arg);
void				exit_error_numeric(char *arg);
void				exit_error_too_many_args(void);
void				cleanup_and_exit(int status);
void				ft_exit(char **args);
/************************************************************************************************************************************************************************ */
// env ==> my_env
t_env				*ft_create_env_node(char *env);
t_env				*init_env_list(char **env);
int					env_len(t_env *env);
char				*ft_join_key_value(char *key, char *value);
char				**env_list_to_array(t_env *env_list);
/************************************************************************************************************************************************************************ */
// garbage collector
void				*ft_gc(size_t n, char flag);
void				fr_ee(t_gc *gc);
t_gc				*create(void *ptr);
void				add(t_gc **gc, t_gc *new);
//*********************************************************************************************************************************************************************** */
/*                   #PARSSING#                                              */
// this one is for the type of quote, whether it is '' or "" or none

// after tokenizing we should know what is the type of each token we have these are the types
typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SEMICOLON,
}					t_token_type;

// it will store value of each token itself,
// and pointer for the next one,and the type of it
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	t_quote_type	quote_type;
	struct s_token	*next;
}					t_token;

// This the parser functions declarations

// This the parser functions declarations

t_list				*parse_cmd(char *input, t_env *env);
t_env				*init_env(char **env);
t_token				*tokenize_input(char *input);
char				*process_input(char *input, int *i,
						t_quote_type *quote_type);
char				*get_operator(char *input, int *i,
						t_quote_type *quote_type);
char				*get_word(char *input, int *i, t_quote_type *quote_type);
t_token_type		get_token_type(char *value);
char				*get_env_value(t_env *env, char *key);
void				expand_variables(t_token *tokens, t_env *env);
char				*case_of_squote(char *word, int *i, char *result);
char				*case_of_dquote(char *word, int *i, char *result,
						t_env *env);
char				*case_of_normal_var(char *word, int *i, char *result,
						t_env *env);
char				*case_of_var_with_next_char_squote(char *word, int *i,
						char *result);
char				*case_of_var_with_next_char_dquote(char *word, int *i,
						char *result);
char				*case_of_var_with_next_char_digit(char *word, int *i,
						char *result);
char				*case_of_var_with_exit_status(int *i, char *result);
char				*case_of_word(char *word, int *i, char *result);
char				*ft_strjoin_char(char *str, char c);
t_list				*parse_tokens(t_token *tokens);
char				**ft_realloc_array(char **arr, char *new_str);
void				free_tokens(t_token *tokens);
t_list				*ft_add_file(t_list *cmds, char *new_str, int flag, char c);

// exit with gc
void imane_exit(int status);

#endif
