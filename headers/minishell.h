/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 05:22:12 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/04 17:29:06 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//------------- libraries -------------------------------------------------

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../LIBFT/libft.h"
# include "../gnl/get_next_line.h"
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <signal.h>
# include <errno.h>
# include <paths.h>
# include <fcntl.h>
//------------- typedefs --------------------------------------------------

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define ERROR 1
# define SUCCESS 0

# define APPND ">>"
# define I_REDI "<"
# define O_REDI ">"
# define HRDC "<<"

//-----------------abstract syntax tree-------------------------------------

//---------------------------structs----------------------------------------

typedef enum s_tokens{
	PIPE,
	WORD,
	AND,
	OR,
	O_BCK,
	C_BCK,
	SPC,
	APPEND,
	HERDOC,
	S_QUOTES,
	D_QUOTES,
	VARIABLE,
	EXPND_VB,
	I_REDIRECTION,
	O_REDIRECTION,
	CMD,
	SOL,
}	t_tokens;

typedef struct s_cmd
{
	char			*str;
	t_tokens		type;
	bool			opr;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_exc
{
	char			**str;
	char			*flg;
	int				in_file;
	int				out_file;
	struct s_exc	*next;
}	t_exc;

typedef struct s_expnd
{
	int		i;
	int		j;
	int		count;
	char	*var;
	int		*tab;
	char	**spltd;
}				t_expnd;

typedef struct s_pipe
{
	int		p_c;
	int		**p_fd;
}	t_pipe;

typedef struct s_types
{
	int		tmp_type;
	int		old_type;
	bool	operator;
}			t_types;
typedef struct s_data
{
	t_cmd	*cmd;
	t_env	*env;
	t_exc	*exc;
	t_pipe	*pps;
	t_types	*tokens;
	char	**envp;
	char	**avm;
	int		g_xst;
	char	path[PATH_MAX];
}	t_data;
typedef struct s_vb
{
	int		i;
	int		j;
	int		check;
	int		k;
}	t_vb;

int	g_xst;

int		ft_cases1(t_cmd *tmp);
int		operator_handler2(char *str, int type);
int		here_doc(t_cmd *delemiter, t_data *data);
int		ft_open(int *out_file, int *in_file, int j, char *str);
int		ft_pwd(t_data *data);
char	**parse_args1(t_data *data);
int		ft_check_tokens(t_cmd *cmd);
int		ft_check_toekns2(t_data *data);

//---------------- test_functions --------------------------------------------

int		redirection_handler(char a,	char b, int old_type, bool *operator);
void	join_unspaced(t_cmd **node,	t_cmd **node_next, t_data **data);

//--------------------------------lst-functions---------------------------

bool	check_one(t_cmd *node, t_cmd *node_next);
void	sorted_env(t_env *env, t_data *data);
int		check_return(int i, char *str, int *in_file, int her_file);
//--------------------------------syntax_error_functions-------------------

t_cmd	*get_list(t_cmd *node, char *str, t_tokens type, t_data *data);
void	quotes_error(char c);
void	syntax_error(void);
void	unexpected_token(char c);
char	get_quote(char line);
bool	ft_break(int a, int b);
char	*rmv_quotes(char	*str);
int		search_spc_node(t_cmd **cmd);
char	*trim_quote(char *str);
char	**parse_args(t_data *data);
char	*env_to_str(t_env *env, t_data *data);

//----------------------------------------------------------------------------

int		quote_check(int old_type, char	*line, int	*i, int	*words);
t_cmd	*create_node(char *content, t_tokens type, t_data *data);
void	ft_create_cmd(t_cmd *cmd);
int		get_token(char *line, int *i, int words, t_data *data);
void	var_handler(char *line, int *i, int *words, int *type);
bool	quote_handler(char *line, int *i, int *words, int *type);
int		get_token_type(char line, bool *operator);
int		check_operatrs_first(t_data *data);
int		check_operators_sec(t_data *data);
int		operator_handler(char *str, int type);
void	ft_space_skip(char **line, int *i);
bool	env_check(char *str, t_data *data);
bool	rm_quotes(t_data **data);
void	herdoc_handler(t_data *data, int *her_file, int status);
void	ft_case1(char **str, int *i);
void	print_exc(t_exc *exc);
char	**i_split(const char *s, char *c);
void	mini_perror(char *str);
char	*ft_join_exc(char *str, char *cmd);
void	ft_join1(char **str);
void	ft_join(char **str);
//--------------------------------------------------------------------------
void	add_back_exc(t_exc **exc, t_exc *new_node);
int		ft_count_pipes(t_data *data);
int		ft_pipe_check(char *line, t_tokens type);
bool	ft_check_input(char *input);
void	ft_shell(char *line, t_data *data, t_env *env, char **envp);
t_cmd	*pipe_parse(char *s, t_cmd *cmd);
char	*double_quotes_check(char *line);
bool	number_of_quotes(char *line);
char	*line_check(char *path);
int		ft_only_words(char *str, char *line, t_tokens *token);
int		is_words(char c, char *str, t_tokens *token);
int		ft_only_words(char *str, char *line, t_tokens *token);
void	cmd_list(char *str, t_tokens token, bool operator, t_data *data);
int		build_token_list(char *line, t_data *data, int *her_file);
bool	check_old_type(char *line, int *i, int *words, int *old_type);
int		first_check(char *line, char *str);
t_env	*env_list(char	**envp);
void	print_env(t_env *env, t_data *data);
int		identify_builtin(t_data *data, t_exc	*cmd);
void	add_back_env(t_env	**env, t_env	*new_node);
t_env	*new_node_env(char	*key, char	*value);
t_cmd	*new_node_cmd(char	*str, t_tokens type, bool operator, t_data *data);
void	var_expnd(t_data	*data);
int		ft_check(char *str);
void	fill_export(char	*str, t_data	*data);
int		exctab_len(char **tab);
char	*get_strredir(int j);
void	do_export(t_data	*data, char	*key, char	*val, bool mode);
void	sort_env(char **tab, int tab_len);
size_t	envtab_len(char **env);
//----------------print fucntions------------------------------------------/

void	print_lst(t_cmd **cmd);
void	print_cmd(t_cmd *cmd);

char	*get_redirection(t_exc **exc, int her_file, int *result);
int		rederection_check(t_exc **exc, int her_file);
//----------------Built-ins------------------------------------------------/
int		check_identifier(char	*str);
void	ft_cd(t_data	*data);
void	ft_echo(t_exc	*exc);
void	ft_export(t_exc	*cmd, t_data	*data);
void	ft_unset(t_exc	*cmd, t_data *data);
void	ft_exit(t_exc	*cmd);
char	*get_ev(t_data *data, char *str);

//---------exc_list---------------------------------------------------------/

char	*flag_str(t_cmd *cmd);
void	fill_exclist(t_cmd *cmd, t_data *data);
char	**prep_excstr(t_cmd *cmd);
void	exc_list(char **str, t_data *data);
t_exc	*new_node_exc(char **str, t_data *data);
void	cmd_call(t_exc *exc, t_data *data, char **envp, int her_file);

//-------------Execve--------------------------------/
void	exec_cmd(t_exc *exc, char *bin, char **envp);
char	*get_path(char **cmd, t_data *data, int *check);
void	ft_dup2(int *in_file, int *out_file, int fd0, int fd1);
void	ft_cat(char **bin, char *path_split, char *cmd);
void	ft_dup(int *in_save, int *out_save);
//-----------signals-----------------/
void	signals_handler(void);
void	handler(int sig);
void	ignore_signal(void);
void	here_handler(int sig);
//----------------pipes-------------------------------------------/
void	redirect_inpipes(t_exc	*tmp, int status, t_data	*data, int i);
int		check_pipes(t_exc	*exc);
int		**create_pipes(int count);
void	exec_pipes(t_exc	*exc, t_data	*data, int her_file, char **envp);
int		*save_stds(void);
void	close_fds(t_data	*data);
//----------------free_functions-------------------------------------------/
char	**free_tab(char **tab);
void	free_cmd(t_data *data);
void	free_exc(t_data *data);
void	free_env(t_env *env);
//----------------Var_expander----------------------------------/
char	*find_var(char *var, t_env *env);
char	*join_expnd(char **spltd, t_env *env, int count);
char	*prep_expnd(char	*var, t_env *env, t_cmd *cmd);
char	**fill_spltd(char *var, char **spltd, int count);
int		*char_counter(char *var, int count, t_cmd *cmd);
int		word_counter(char	*var);
void	check_variables(t_cmd	*tmp, t_data	*data);
#endif
