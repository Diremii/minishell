/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:15:05 by humontas          #+#    #+#             */
/*   Updated: 2025/04/03 16:09:42 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		// size_t	i;
		// while (current)
		// {
		// 	ft_printf("Infile : %s\nOutfile : %s\nLimiter : %s\nhere_doc : %d\nappend : %d\n", current->infile, current->outfile, current->limiter, current->here_doc, current->append);
		// 	i = 1;
		// 	ft_printf("Command : ");
		// 	if (current->cmd_param && current->cmd_param[0])
		// 		ft_printf("%s\n", current->cmd_param[0]);
		// 	ft_printf("Flags : ");
		// 	while (current->cmd_param && current->cmd_param[i])
		// 	{
		// 		ft_printf("%s, ", current->cmd_param[i]);
		// 		i++;
		// 	}
		// 	ft_printf("\n\n");
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
