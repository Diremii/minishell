/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:10:48 by humontas          #+#    #+#             */
/*   Updated: 2025/04/01 18:45:41 by ttremel          ###   ########.fr       */
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

typedef enum e_token_type
{
	IN = 1, // <
	HEREDOC = 2, // <<
	OUT = 3, // >
	APPEND = 4, // >>
	PIPE = 5, // |
	CMD = 6,
	ARG = 7,
	REDIR = 8
}	t_token_type;

typedef struct s_cmd
{
	int				here_doc;
	int				append;
	char			*infile;
	char			*outfile;
	char			*limiter;
	char			**cmd_param;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_token 	*next;
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
	char	**envp;
	char	**paths;
	t_token	*tokens;
	t_cmd	*cmd;
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
void	redirection_file_handling(char *input , t_token *tokens, size_t *i);

/* COMMAND */
t_cmd	*new_cmd(char **args);
t_cmd	*cmdlast(t_cmd *lst);
void	cmd_add_back(t_cmd **lst, t_cmd *new);
void	cmd_add_front(t_cmd **lst, t_cmd *new);
char	**get_list_of_args(t_token **tokens);
int		typing_heredoc(t_token **current, t_cmd **cmd);
int		typing_cmd(t_token **current, t_cmd **cmd);
int		get_command(t_token *tokens, t_data *data);
int		set_out(t_data *data);
int		set_in(t_data *data);

/* EXEC */
pid_t	pipex(int fd[2], t_data *data, t_cmd **cmd);
pid_t	last_process(int p_fd[2], int fd[2], t_data *data, t_cmd **cmd);
void	child_process(int p_fd[2], int fd[2], t_data *data, t_cmd **cmd);
void	parent_process(int p_fd[2], int fd[2], t_data *data);
void	ft_exec(int p_fd[2], int fd[2], t_data *data, t_cmd **cmd);
void	close_fd(int fd[2]);
void	close_n_exit(int fd[2], t_cmd **cmds);
void	close_all(int p_fd[2], int fd[2], t_cmd **cmds);
void	error_msg(int err, char *error);
int		check_all_access(t_cmd **cmd, t_data *data, int here_doc);
int		open_fd(int fd[2], t_cmd *cmd);
int		ft_pipe(t_data *data);
int		pipe_in_pipe(t_data *data, t_cmd **cmd);
int		here_doc(char *lim);
int		wait_all_pid(pid_t pid, size_t size);

/* PARSING */
int		is_empty_string(char *str);
int		init_parsing(char *str);
int		check_syntax_error(t_token *tokens);

/* UTILS */
size_t	cmdsize(t_cmd *cmds);
char	**expand_alloc(char **list, size_t old_size, size_t new_size);
void	exit_error(char *str, int exit_code);
int		is_opperator(char c);

/* FREE */
void	free_all(char **list);
void	cmd_clear(t_cmd **lst);
void	clear_tokens(t_token **tokens);


#endif