/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:15:05 by humontas          #+#    #+#             */
/*   Updated: 2025/04/07 16:20:52 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	g_signal_pid;

int main(int ac, char **av, char **envp)
{
	t_history	*history;
	t_token		*tokens;
	t_data		data;
	char		*input;

	(void)ac;
	(void)av;
	history = malloc(sizeof(t_history));
	tokens = NULL;
	data.envp = envp;
	if (!envp[0])
		data.envp = NULL;
	init_history(history);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		tokens = init_token(input, &data);
		if (!tokens)
		{
			free(input);
			continue ;
		}
		init_parsing(input);
		get_command(tokens, &data);
		
		// debug : show cmd content
		// t_cmd	*current = data.cmd;
		// t_redir	*current_redir;
		// size_t	i;
		// while (current)
		// {
		// 	i = 0;
		// 	ft_printf_fd("Command : ", 2);
		// 	ft_printf_fd("%s\n", 2, current->cmd);
		// 	ft_printf_fd("Infiles : ", 2);
		// 	current_redir = current->redir_in;
		// 	while (current_redir)
		// 	{
		// 		ft_printf_fd("[%s, %d, %d], ", 2, current_redir->file, current_redir->type, current_redir->fd);
		// 		current_redir = current_redir->next;
		// 	}
		// 	ft_printf_fd("\n", 2);
		// 	current_redir = current->redir_out;
		// 	ft_printf_fd("Outfiles : ", 2);
		// 	while (current_redir)
		// 	{
		// 		ft_printf_fd("[%s, %d, %d], ", 2, current_redir->file, current_redir->type, current_redir->fd);
		// 		current_redir = current_redir->next;
		// 	}
		// 	ft_printf_fd("\n", 2);
		// 	ft_printf_fd("Flags : ", 2);
		// 	while (current->flags && current->flags[i])
		// 	{
		// 		ft_printf_fd("%s, ", 2, current->flags[i]);
		// 		i++;
		// 	}
		// 	ft_printf_fd("\n\n", 2);
		// 	current = current->next;
		// }
		// ------------------------------------------------------------
		ft_pipe(&data);
		add_to_history(history, input);
		cmd_clear(&data.cmd);
		clear_tokens(&tokens);
		free(input);
	}
	free(tokens);
	close(history->fd);
	free(history->last_command);
	free(history->path);
	free(history);
	clear_history();
}
