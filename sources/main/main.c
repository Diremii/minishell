/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:15:05 by humontas          #+#    #+#             */
/*   Updated: 2025/03/20 17:20:36 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_history	*history;
	char		*input;

	(void)ac;
	(void)av;
	(void)envp;
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
