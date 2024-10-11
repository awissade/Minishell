/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awissade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:42:39 by awissade          #+#    #+#             */
/*   Updated: 2024/10/09 15:48:32 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../src/libft/libft.h"
# include "../src/get_next_line/get_next_line.h"
# include <sys/wait.h>
# include <errno.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>

# define EXEC 0
# define REDIR 1
# define HEREDOC 2
# define PIPE 3
# define LOGOP 4
# define SUBSHELL 5

# define SYNTAX_ERROR 2

# define UNCLOSED_QUOTES 0
# define UNEXPECTED 1
# define UNCLOSED_PARENTHESES 2

# define PERMISSION_DENIED 126

# define NO_SUCH_FILE_OR_DIR 127
# define EXECUTION_FAILED 1
# define CHILD_TERM_SIGINT 130
# define CHILD_TERM_SIGQUIT 131

typedef struct s_token
{
	char			type;
	char			*content;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_cmd
{
	int	type;
}				t_cmd;

typedef struct s_execcmd
{
	int		type;
	char	**av;
}				t_execcmd;

typedef struct s_redircmd
{
	int				type;
	char			*file;
	int				mode;
	int				fd;
	struct s_cmd	*cmd;
}				t_redircmd;

typedef struct s_heredoccmd
{
	int				type;
	char			*input;
	struct s_cmd	*cmd;
}				t_heredoccmd;

typedef struct s_pipecmd
{
	int				type;
	struct s_cmd	*left;
	struct s_cmd	*right;
}				t_pipecmd;

typedef struct s_logopcmd
{
	int				type;
	int				mode;
	struct s_cmd	*left;
	struct s_cmd	*right;
}				t_logopcmd;

typedef struct s_subshellcmd
{
	int		type;
	char	*content;
}				t_subshellcmd;

typedef struct s_localvar
{
	unsigned char	exit_status;
	int				active;
	char			*pwd;
	char			*oldpwd;
	int				path_unset;
	char			*default_path;
}				t_localvar;

typedef struct s_tree_elements
{
	t_execcmd		*exec;
	t_redircmd		*redir;
	t_heredoccmd	*heredoc;
	t_pipecmd		*pipe;
	t_logopcmd		*logop;
}				t_tree_elements;

typedef struct s_wildcard
{
	int	slen;
	int	plen;
	int	sidx;
	int	pidx;
	int	wildcard;
	int	next_to_wildcard_idx;
	int	sbacktrack_idx;
}				t_wildcard;

char		*handle_nonquoted_string(char *arg, char *newarg, \
		int *idx, char *arr);
void		minishell(void);
char		***get_env(void);
int			*get_termsig(void);
int			*get_heredoc_termsig(void);
t_localvar	*get_localvar(void);

/*Garbage collector*/
void		*safe_alloc(size_t size);
void		garbage_collector(void);

/*Utils*/
char		*strjoin(char *s1, char *s2);
char		*substr(char *s, unsigned int start, size_t len);
char		*cm_strdup(char		*src);
int			ft_dblptrlen(char **av);
void		ft_dblfree(char **ptr);
char		**get_copy_with_malloc(char **strs);
char		*ft_strncpy(char *dest, char *src, int n);
char		*ft_strndup(char *str, size_t n);
char		*ft_getenv(char *variable);
int			compare_variables(char *var1, char *var2);
char		*cm_itoa(int n);
int			ft_isspace(char c);
int			cm_strstr(char *str, char *to_find);
char		*remove_trailing_whitspaces(char *str);
char		**split(char *str, char c);
char		**split_argument(char *arg, int numof_args);

/*Parsing*/
t_cmd		*parsing(char *line);
t_cmd		*parse_cmd(t_token *tokens_ptr);
t_token		*tokenizer(char *commandline);
t_cmd		*parse_pipe(t_token *tokens_ptr);
t_cmd		*parse_logop(t_token *tokens_ptr);
t_cmd		*parse_redir(t_token *tokens_ptr);
t_token	*peek_for_logop(t_token *tokens_ptr);
t_cmd		*parse_subshell_block(t_token *tokens_ptr);
t_cmd		*parse_exec(t_token *tokens_ptr);
t_token		*peek(t_token *tokens_head, char type);
char		**get_command_args(t_token *tokens_head);
char		*expand(char *commandarg);
char		*add_backlash_quoting(char *str);
char		*expand_element(char *commandarg);
char		*handle_doublyquoted_string(char *arg, char *newarg, int *idx, \
		char *arr);
char		**expand_cmd_variables(char **av);
int			is_special_dollar_sign(char *arg, int idx);
int			isdynamic_assignement(char *arg);
char		*handle_variables(char *newarg, char *arg, int *idx, int flag);
int			validator(t_token *tokens);
int			check_following(t_token *tokens);
void		check_numof_heredocs(t_token *tokens);
int			syntax_error(int flag, char *token);
void		handle_signals(int signum);
t_localvar	*get_localvar(void);
void		skip_spaces(char **str);
char		*get_token_content(char *commandline, int len);
void		advance_pointer(char **ptr, int len);
int			quoted_string_length(char *str);
int			control_operators_length(char *str);
int			subshell_block_length(char *string);
void		initialize_localvar(t_localvar *localvar);
char		*remove_quotes(char *str);
char		*getother(char *arg, int *start, int *flag, char *holder);
char		*getenv_locally(char *variable_name, t_localvar *localvar);
char		*getvariable(char *arg, int *start, t_localvar *localvar);
char		*get_heredoc_input(char *limiter);
char		*char_to_string(char character);
char		*get_type_element(char type);
char		*catch_wildcards(char *arg);
char		*remove_quotes(char *str);
int			len_without_quotes(char *str);
char		*return_nameof_variable(char *arg, int *start);
char		*get_heredoc_input(char *limiter);
char		*substr_replace(char *str, char *substr, int start, int place_len);
int			valid_char(char c);
void		increment_indexes(int *var1, int *var2);
int			name_isvalid(char *var);
char		**split_var(char *str, char *sep);
void		print_env(char **env);
char		**remove_invalid_variables(char **av);
int			string_length(char *commandline);
int			block_length(char *arg);
char		*getvariable_clean(char *arg, char *newarg, int *idx, int flag);
char		*add_quotes(char *str);
int			nonquoted_string_length(char *arg, int idx);
int			is_special_dollar(char *arg, int idx);

/*Constructor functions*/
t_cmd		*pipecmd(t_cmd *left, t_cmd *right);
t_cmd		*logopcmd(int mode, t_cmd *left, t_cmd *right);
t_cmd		*redircmd(char *file, int mode, int fd, t_cmd *cmd);
t_cmd		*heredoccmd(char *input, t_cmd *cmd);
t_cmd		*subshell_block(char *content);
t_cmd		*execcmd(char **av);

/*execution*/
int			runcmd(t_cmd *cmd);
int			execution(t_execcmd *exec);
int			redirection(t_redircmd *redir);
int			heredoc(t_heredoccmd *heredoc);
int			piping(t_pipecmd *pipe_symbol);
int			logop(t_logopcmd *logop);
char		**strsplit(char *str, char sep);
int			execute_subshell_block(t_subshellcmd *subdhell_block);
char		*get_cmd_path(char *cmd);
char		*get_command(char *command);
int			isbuiltin(char *cmd);
int			lento_equalsign(char *str);
int			lookfor_variable(char *variable, char **env);
int			numof_valid_variables(char **av);
int			*isreturning(void);

/*builtins*/
int			cd(char **av);
void		change_pwd(char **env, t_localvar *localvar);
int			echo(char **av);
int			builtin_env(void);
int			builtin_exit(char **av);
int			*inparent(void);
int			builtin_export(char **av);
void		add_variable(char *var, char **env);
void		update_variable(char *var, char **env, int var_with_value);
int			export_variable(char *var);
void		concat_to_var(char *var, char **env);
int			pwd(void);
int			unset(char **av);
void		panic(int status);
void		end(int status);
pid_t		safe_fork(void);

#endif
