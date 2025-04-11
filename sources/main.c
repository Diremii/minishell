/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:15:05 by humontas          #+#    #+#             */
/*   Updated: 2025/04/11 13:43:17 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	g_signal_pid;

char	**envp_dup(char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			free_all(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

int	main(int ac, char **av, char **envp)
{
	t_data		data;
	char		*input;

	(void)ac;
	(void)av;
	data.envp = envp;
	//data.envp = envp_dup(envp);
	if (!data.envp)
		return (1);
	setup_signals();
	init_history(&data.history);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		data.tokens = init_token(input, &data);
		add_to_history(&data.history, input);
		// ------------------------debug--------------------------
		t_token		*tmp = NULL;
		tmp = data.tokens;
		data.cmd = NULL;
		
		while (tmp)
		{
			printf("Token: %s, Type: %d\n", tmp->str, tmp->type);
			tmp = tmp->next;
		}
		// -------------------------------------------------------
		//if (!data.tokens || init_parsing(input, data.tokens, &data))
		//	continue ;
		//get_command(data.tokens, &data);
		//ft_pipe(&data);
		clear_all(&data, input);
	}
	clear_history_data(&data);
}
