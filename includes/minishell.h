/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:10:48 by humontas          #+#    #+#             */
/*   Updated: 2025/04/09 18:38:55 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include "libft/libft.h"
# include "libft/printf/ft_printf.h"

# define ERR_FILE "\033[31m[Minishell]\033[37m\
 No such file or directory\n"
# define ERR_ARGS "\033[31m[Minishell]\033[37m\
 Too many arguments\n"
# define ERR_SYNTAX "\033[31m[Minishell]\033[37m\
 Syntax error near unexpected token `newline'\n"
# define ERR_TOKEN "\033[31m[Minishell]\033[37m\
 Syntax error near unexpected token `%s'\n"
# define ERR_UNKNOWN "\033[31m[Minishell]\033[37m\
 %s: Command not found\n"
# define ERR_ACCESS "\033[31m[Minishell]\033[37m\
 %s: Permission denied\n"
# define ERR_NO_FILE "\033[31m[Minishell]\033[37m\
 %s: No such file or directory\n"

extern pid_t	g_signal_pid;

typedef enum e_token_type
{
	IN = 1,
	HEREDOC = 2,
	OUT = 3,
	APPEND = 4,
	PIPE = 5,
	CMD = 6,
	ARG = 7,
	REDIR = 8
}	t_token_type;

typedef struct s_redir
{
	t_token_type	type;
	struct s_redir	*next;
	struct s_redir	*prev;
	char			*file;
	char			*limiter;
	int				fd;
	int				here_doc;
}			t_redir;

typedef struct s_cmd
{
	struct s_cmd	*prev;
	struct s_cmd	*next;
	t_redir			*redir_in;
	t_redir			*redir_out;
	char			*cmd;
	char			**flags;
}	t_cmd;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_history
{
	char	*path;
	char	*last_command;
	int		fd;
}	t_history;

typedef struct s_data
{
	int			exit_status;
	char		**envp;
	char		**paths;
	t_token		*tokens;
	t_cmd		*cmd;
	t_history	history;
}	t_data;

/* HISTORY */
void	init_history(t_history *history);
void	add_to_history(t_history *history, const char *command);

/* TOKENS */
t_token	*init_token(char *input, t_data *data);
t_token	*add_token_to_list(t_token **head, char *str, t_token_type type);
char	*path_of(char *cmd, char **env);
char	*cut_quote(char *str);
char	*get_flag(char *input, size_t *i);
void	handle_command(char *input, size_t *i, t_token **tokens, t_data **data);
void	handle_operator(char *input, size_t *i, t_token **tokens);
void	redirection_file_handling(char *input, t_token *tokens, size_t *i);

/* COMMAND */
t_redir	*new_redir(char *content, t_token_type type);
t_redir	*redirlast(t_redir *lst);
t_cmd	*new_cmd(char **args);
t_cmd	*cmdlast(t_cmd *lst);
void	redir_add_front(t_redir **lst, t_redir *new);
void	redir_add_back(t_redir **lst, t_redir *new);
void	cmd_add_back(t_cmd **lst, t_cmd *new);
void	cmd_add_front(t_cmd **lst, t_cmd *new);
int		get_command(t_token *tokens, t_data *data);
int		add_redir(t_token **tokens, t_redir **redir);
int		add_cmd(t_cmd **cmd, t_data *data);
int		add_out(t_cmd **cmd, t_token **current);
int		add_in(t_cmd **cmd, t_token **current);

/* BUILT-INS */
void	ft_cd(t_data *data, char **args);
void	ft_export(t_data *data, char **args);
void	ft_unset(t_data *data, char **args);
void	ft_env(t_data *data);
void	ft_echo(char **args);
void	ft_pwd(void);

/* EXEC */
pid_t	pipex(int fd[2], t_data *data, t_cmd **cmd);
void	ft_execve(t_cmd *cmd, t_data *data, int p_fd[2]);
void	close_fd(int fd[2]);
void	close_n_exit(int fd[2], t_cmd **cmds);
void	close_all(t_redir **redir);
int		error_msg(char *msg, char *error);
int		check_all_access(t_cmd *cmd);
int		arg_after_redir(t_cmd **cmd, t_token **current);
int		ft_exec(t_data *data);
int		single_cmd(t_data *data);
int		ft_pipe(t_data *data);
int		pipe_in_pipe(t_data *data, t_cmd **cmd);
int		here_doc(char *lim);
int		wait_all_pid(void);
int		redir_out(t_cmd **cmd);
int		redir_in(t_cmd **cmd);
int		wait_pid(void);

/* PARSING */
int		is_empty_string(char *str);
int		init_parsing(char *str, t_token *tokens);
int		check_syntax_error(t_token *tokens);

/* UTILS */
size_t	size_of_list(char **list);
size_t	cmdsize(t_cmd *cmds);
char	**expand_alloc(char **list, size_t old_size, size_t new_size);
void	exit_error(char *str, int exit_code);
int		is_opperator(char c);
void	setup_signals(void);
int		print_syntax_error(int error, char *type);

/* FREE */
void	free_all(char **list);
void	cmd_clear(t_cmd **lst);
void	redir_clear(t_redir **lst);
void	clear_tokens(t_token **tokens);
void	clear_history_data(t_data *data);

#endif