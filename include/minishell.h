/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senayat <senayat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:26:20 by senayat           #+#    #+#             */
/*   Updated: 2024/11/08 09:10:44 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

# define NORMAL "\033[0m"
# define RED "\033[31;1m"
# define GREEN "\033[32;1m"

typedef enum e_toktype
{
	TOK_ILLEGAL,
	TOK_SPC_CHR,
	TOK_NORMAL,
	TOK_STR,
	TOK_LIT_STR,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_HEREDOC,
	TOK_APPEND,
	TOK_PIPE,
	TOK_END,
}	t_toktype;

typedef enum e_action
{
	ACT_COMMAND,
	ACT_PIPE
}	t_action;

typedef struct s_token
{
	t_toktype		type;
	char			*literal;
	struct s_token	*next;
}	t_token;

typedef struct s_redirin
{
	bool				heredoc;
	char				*arg;
	struct s_redirin	*next;
}	t_redirin;

typedef struct s_redirout
{
	bool				append;
	char				*file;
	struct s_redirout	*next;
}	t_redirout;

typedef struct s_arg
{
	char			*arg;
	struct s_arg	*next;
}	t_arg;

typedef struct s_command
{
	t_arg		*args;
	t_redirin	*in;
	t_redirout	*out;
}	t_command;

typedef struct s_pipe
{
	struct s_tree	*first;
	struct s_tree	*second;
}	t_pipe;

typedef union u_targ
{
	t_command	command;
	t_pipe		pipe;
}	t_targ;

typedef struct s_tree
{
	t_action	action;
	t_targ		arg;
}	t_tree;

typedef struct s_env
{
	char			*var;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_msh
{
	t_int	exit_code;
	bool	should_exit;
	t_int	pid;
	t_token	*token;
	t_tree	*tree;
	t_env	*env;
	char	*line;
	char	*heredoc;
}	t_msh;

// -- builtin
bool	free_msh(t_msh *sh);
bool	free_msh_not_env(t_msh *sh);
bool	exit_msh(t_msh *sh, int code);
bool	execute_builtin(t_msh *sh, char *cmd, char **args);
bool	execute_exit(t_msh *sh, char **args);
bool	execute_pwd(t_msh *sh, char **args);
bool	execute_env(t_msh *sh, char **args);
bool	execute_chdir(t_msh *sh, char **args);
bool	execute_echo(t_msh *sh, char **args);
bool	execute_export(t_msh *sh, char **args);
bool	execute_unset(t_msh *sh, char **args);
// -- end builtin

// -- env
bool	init_env_var(t_env **env, char **envp);
bool	deinit_env_var(t_env **env);
char	*get_env_var(t_msh *sh, char *s);
char	*get_env_var_raw(t_msh *sh, char *s);
bool	is_valid_env_var(char *var);
bool	set_env_var(t_msh *sh, char *var, char *val);
bool	remove_env_var(t_msh *sh, char *var);
t_env	*env_from_envstr(char *s);
char	**env_to_envp(t_env *env);
// -- end env

// -- execute
bool	execute_act_command(t_msh *sh, t_tree *tree);
bool	execute_act_pipe(t_msh *sh, t_tree *tree);
bool	execute_command(t_msh *sh, t_tree *tree);
// -- end execute

// -- signals
void	sighandler_int(int sig);
void	sighandler_quit(int sig);
// -- end signals

// -- handle line
bool	isempty_line(char *s);
bool	handle_line(t_msh *sh);
// -- end handle line

int		tokenize(char *s, t_token **token);

// -- interpolation
char	*take_variablename(char *s);
int		str_interpolate_var(t_msh *sh, char **s, char *str);
bool	str_interpolation(t_msh *sh, char **s);
bool	interpolate_into_strs(t_msh *sh, t_token **token);
// -- end interpolation

// -- tokenize
bool	merge_literals_together(t_token **token);
int		free_tokens(int status, t_token **token);
int		display_tokenization_error_and_free(int status, t_token **token);
int		feed_until_next(char *s, char **into);
int		feed_until_enduqstr(char *s, char **into);
bool	cleanse_tokens(t_token **token);
bool	parse_tokens(t_token *tokens, t_tree **tree);
// -- end tokenzie

// -- parse
bool	free_tree(t_tree **tree);
bool	parse_error(t_tree **tree, int err, t_token *token);
bool	parse_handle_strs(t_token *tokens, t_tree **tree);
bool	parse_handle_redirs(t_token *tokens, t_tree **tree);
bool	parse_handle_pipe(t_token *tokens, t_tree **tree);
bool	is_directory(char *path);
bool	is_file(char *path);
bool	is_executable(char *path);
bool	is_builtin(char *name);
char	*path_join(char *path, char *sub);
char	*find_file(t_msh *sh, char *path);
char	**command_args_to_tab(t_arg *arg);
// -- end parse

// -- redirections
char	*get_heredoc_content(t_msh *sh, char *end);
char	*get_heredoc(t_msh *sh, char *end);
bool	handle_redirections(
			t_msh *sh, t_command *cmd, int *save_stdin, int *save_stdout);
void	restore_redirections(int save_stdin, int save_stdout);
// -- end redirections

extern bool	g_minish_exec;

#endif // MINISHELL_H
