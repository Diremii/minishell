/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:15:05 by humontas          #+#    #+#             */
/*   Updated: 2025/03/24 16:24:53 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(void)
{
	t_history	*history;
	t_minishell	*data;	
	char		*input;

	data = malloc(sizeof(t_minishell));
	if (!data)
		exit_error("minishell: Memory allocation failed\n", 1);
	history = malloc(sizeof(t_history));
	if (!history)
		exit_error("minishell: Memory allocation failed\n", 1);
	init_history(history);
	while (1)
	{
		input = readline("minishell > ");
		if (!input)
			break ;
		init_parsing(input);
		add_to_history(history, input);
		free(input);
	}
	close(history->fd);
	clear_history();
}
