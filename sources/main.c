/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:15:05 by humontas          #+#    #+#             */
/*   Updated: 2025/04/03 10:25:07 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	t_data		data;
	char		*input;

	(void)ac;
	(void)av;
	data.envp = envp;
	if (!envp[0])
		data.envp = NULL;
;	init_history(&data.history);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		data.tokens = init_token(input, &data);
		init_parsing(input);
		//get_command(tokens, &data);
		add_to_history(&data.history, input);
		clear_tokens(&data);
		free(input);
	}
	clear_history_data(&data);
}
