/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:15:05 by humontas          #+#    #+#             */
/*   Updated: 2025/04/09 16:12:49 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	g_signal_pid;

int	main(int ac, char **av, char **envp)
{
	t_data		data;
	char		*input;

	(void)ac;
	(void)av;
	data.envp = envp;
	if (!envp[0])
		data.envp = NULL;
	setup_signals();
	init_history(&data.history);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		data.tokens = init_token(input, &data);
		init_parsing(input, data.tokens);
		// t_token *tmp = data.tokens;
		// while (tmp)
		// {
		// 	printf("Type: %d, Str: %s\n", tmp->type, tmp->str);
		// 	tmp = tmp->next;
		// }
		add_to_history(&data.history, input);
		get_command(data.tokens, &data);
		ft_pipe(&data);
		clear_tokens(&data.tokens);
		cmd_clear(&data.cmd);
		free(input);
	}
	clear_history_data(&data);
}
