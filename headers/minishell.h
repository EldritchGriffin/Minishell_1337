//------------- global-header-file -----------------------------------------

#ifndef MINISHELL_H
# define MINISHELL_H

//------------- libraries -------------------------------------------------

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../LIBFT/libft.h"
# include <stdbool.h>
# include <stdlib.h>

//------------- typedefs --------------------------------------------------



# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define ERROR 1
# define SUCCESS 0

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
	SOL,
} t_tokens;

typedef struct s_cmd
{
	char 			*str;
	t_tokens 		type;
	struct s_cmd 	*next;
	struct s_cmd    *prev;
}   				t_cmd;

typedef	struct	s_env
{
	char			*key;
	char			*value;
	struct	s_env	*next;
}					t_env;

typedef struct s_data
{
	t_ptr 		*ptrs;
	t_cmd 		*cmd;
	t_env       *env;
}				t_data;

//-------------- enum strcut contains ---------------------------------------


//---------------- test_functions --------------------------------------------
int redirection_handler(char a , char b, int old_type);
void       join_unspaced(t_cmd **node, t_cmd **node_next, t_data **data);
//--------------------------------lst-functions---------------------------
bool check_one(t_cmd *node, t_cmd *node_next);
void    sorted_env(t_env *env, t_data *data);
//--------------------------------syntax_error_functions-------------------

t_cmd *get_list(t_cmd *node, char *str, t_tokens type, t_data *data);

void    quotes_error(char c);
void    syntax_error(void);
void    unexpected_token(char c);
char   	get_quote(char line);
bool 	ft_break(int a, int b);
char	*rmv_quotes(char	*str);
int     search_spc_node(t_cmd **cmd);
char     *trim_quote(char *str);
char    **parse_args(t_data *data);


//----------------------------------------------------------------------------
int     quote_check(int old_type, char  *line, int *i, int *words);
t_cmd  	*create_node(char *content, t_tokens type, t_data *data);
void    ft_create_cmd(t_cmd *cmd);
void   	get_token(char *line, int *i, int start, t_data *data);
void    var_handler(char *line, int *i, int *words, t_data *data, int *type);
bool    quote_handler(char *line, int *i, char quote, int *words);
int     get_token_type(char line);
int     check_operators(char f, char s);
void   	ft_space_skip(char **line, int *i);
bool 	env_check(char *str, t_data *data);
//--------------------------------------------------------------------------
int     ft_pipe_check(char *line, t_tokens type);
bool    ft_check_input(char *input);
void    ft_shell(t_data *data, t_env *env);
t_cmd   *pipe_parse(char *s, t_cmd *cmd);
char    *double_quotes_check(char *line);
bool    number_of_quotes(char *line);
char    *line_check(char *path);
int     ft_only_words(char *str, char *line, t_tokens *token);
int     is_words(char c, char *str, t_tokens *token);
int     ft_only_words(char *str, char *line, t_tokens *token);
void   	cmd_list(char *str, t_tokens token, t_data *data);
void     build_token_list(char *line, t_data *data);
int     first_check(char *line, char *str);
void    *ft_malloc(int size, t_ptr **ptrs);
t_env   *env_list(char  **envp);
void    print_env(t_env *env);
int     identify_builtin(t_data *data);
void    add_back_env(t_env  **env, t_env    *new_node);
t_env   *new_node_env(char  *key,   char    *value);
t_cmd   *new_node_cmd(char  *str, t_tokens type, t_data *data);
// void  join_unspaced(t_cmd   **node, t_cmd    **node_next, t_data  *data);

//----------------print fucntions------------------------------------------/
void    print_lst(t_cmd **cmd);
//----------------Built-ins------------------------------------------------/
void	ft_echo(t_data *data);
void	ft_export(t_data	*data);
void	ft_unset(t_data		*data);
#endif
