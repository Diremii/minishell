/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovietguy <sovietguy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:15:05 by humontas          #+#    #+#             */
/*   Updated: 2025/04/19 18:48:21 by sovietguy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal_pid;

static char	**envp_dup(char **envp)
{
	int		i;
	int		j;
	char	**new_envp;

	new_envp = malloc(sizeof(char *) * (size_of_list(envp) + 1));
	if (!new_envp)
		return (NULL);
	j = 0;
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			new_envp[j] = ft_strdup(envp[i]);
			if (!new_envp[j])
			{
				free_tab(new_envp);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	return (new_envp);
}

static int	init_program(t_data **data, t_history *history, char **envp)
{
	*data = get_data(history);
	if (!*data)
		return (0);
	(*data)->envp = envp_dup(envp);
	if (!(*data)->envp)
		return (0);
	(*data)->exit_status = 0;
	setup_signals();
	return (1);
}

static int	handle_input(t_data *data, char **input)
{
	*input = readline("minishell$ ");
	if (!*input)
		return (0);
	data->tokens = init_token(*input, data);
	add_to_history(&data->history, *input);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_data		*data;
	t_history	history;
	char		*input;

	(void)ac;
	(void)av;
	init_history(&history);
	if (!init_program(&data, &history, envp))
		return (1);
	//printf("ptr data : %s\n", data->envp[0]);
	//printf("ptr data : %s\n", get_data(NULL)->envp[0]);
	while (1)
	{
		g_signal_pid = 0;
		if (!handle_input(data, &input))
			break ;
		if (!data->tokens || init_parsing(input, data->tokens, data))
			continue ;
		get_command(data->tokens, data);
		multi_cmd(data);
		clear_all(data, input);
	}
	free_all(data);
}
