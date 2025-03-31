/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:15:05 by humontas          #+#    #+#             */
/*   Updated: 2025/03/31 14:19:52 by ttremel          ###   ########.fr       */
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
		init_parsing(input);
		get_command(tokens, &data);
		
		// debug : show cmd content
		t_cmd	*current = data.cmd;
		size_t	i;
		while (current)
		{
			ft_printf("Infile : %s\nOutfile : %s\nLimiter : %s\nhere_doc : %d\nappend : %d\n", current->infile, current->outfile, current->limiter, current->here_doc, current->append);
			i = 1;
			ft_printf("Command : ");
			if (current->cmd_param[0])
				ft_printf("%s\n", current->cmd_param[0]);
			ft_printf("Flags : ");
			while (current->cmd_param[i])
			{
				ft_printf("%s, ", current->cmd_param[i]);
				i++;
			}
			ft_printf("\n");
			current = current->next;
		}
		add_to_history(history, input);
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
