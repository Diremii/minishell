/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:10:48 by humontas          #+#    #+#             */
/*   Updated: 2025/04/17 12:31:17 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
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
# include "error.h"
# include "struct.h"

extern int	g_signal_pid;

/* HISTORY */
void	init_history(t_history *history);
void	add_to_history(t_history *history, const char *command);

/* TOKENS */
t_token	*init_token(char *input, t_data *data);
t_token	*add_token_to_list(t_token **head, char *str, t_token_type type);
t_list	*handle_dollars(char *str, size_t *i, char quote, t_data *data);
void	handle_command(char *input, size_t *i, t_token **tokens);
void	handle_operator(char *input, size_t *i, t_token **tokens);
void	redirection_file_handling(char *input, t_token *tokens, size_t *i);
char	*replace_dolar_in_str(char *str, t_data *data);
char	*path_of(char *cmd, char **env);
char	*cut_quote(char *str);
char	*get_flag(char *input, size_t *i);

/* COMMAND */
t_redir	*new_redir(char *content, t_token_type type);
t_redir	*redirlast(t_redir *lst);
t_cmd	*new_cmd(char **args);
t_cmd	*cmdlast(t_cmd *lst);
void	redir_add_back(t_redir **lst, t_redir *new);
void	cmd_add_back(t_cmd **lst, t_cmd *new);
int		get_command(t_token *tokens, t_data *data);
int		add_cmd(t_cmd **cmd, t_data *data);
int		add_out(t_cmd **cmd, t_token **current);
int		add_in(t_cmd **cmd, t_token **current);

/* BUILT-INS */
void	ft_cd(t_data *data, char **args);
void	ft_export(t_data *data, char **args);
void	ft_exit(t_data *data, char **args);
void	ft_unset(t_data *data, char **args);
void	ft_env(t_data *data);
void	ft_echo(char **args);
void	ft_pwd(void);

/* EXEC */
void	ft_execve(t_cmd *cmd, t_data *data, int p_fd[2]);
void	close_fd(int fd[2]);
void	close_all(t_redir **redir);
void	wait_all_pid(t_data *data);
void	wait_pid(t_data *data);
int		skip_built_ins(t_data *data);
int		ft_exec(t_data *data);
int		single_cmd(t_data *data);
int		ft_pipe(t_data *data);
int		here_doc(char *lim);
int		redir_out(t_cmd **cmd);
int		redir_in(t_cmd **cmd);

/* PARSING */
int		is_empty_string(char *str);
int		init_parsing(char *str, t_token *tokens, t_data *data);
int		check_syntax_error(t_token *tokens, t_data *data);

/* UTILS */
t_data	*get_data(t_history *history);
size_t	size_of_list(char **list);
size_t	cmdsize(t_cmd *cmds);
void	exit_error(char *str, int exit_code);
void	setup_signals(void);
char	**expand_alloc(char **list, size_t old_size, size_t new_size);
int		ft_strccmp(char *s1, char *s2, char c);

/* FREE */
void	free_all(char **list);
void	cmd_clear(t_cmd **lst);
void	redir_clear(t_redir **lst);
void	clear_tokens(t_token **tokens);
void	clear_history_data(t_data *data);
void	clear_all(t_data *data, char *input);

#endif