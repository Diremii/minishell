/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:15:05 by humontas          #+#    #+#             */
/*   Updated: 2025/03/27 11:30:55 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int main(int ac, char **av, char **envp)
// {
// 	t_history	*history;
// 	t_token		*tokens;
// 	t_data		data;
// 	char		*input;

// 	(void)ac;
// 	(void)av;
// 	history = malloc(sizeof(t_history));
// 	tokens = malloc(sizeof(t_token));
// 	data.envp = envp;
// 	if (!envp[0])
// 		data.envp = NULL;
// 	init_history(history);
// 	while (1)
// 	{
// 		input = readline("minishell > ");
// 		if (!input)
// 			break ;
// 		tokens = init_token(input);
// 		add_to_history(history, input);
// 		free(input);
// 	}
// 	close(history->fd);
// 	clear_history();
// }

int main(int ac, char **av, char **envp)
{
	t_history	*history;
	t_token		*tokens;
	t_data		data;
	char		*input;

	(void)ac;
	(void)av;
	history = malloc(sizeof(t_history));
	tokens = malloc(sizeof(t_token));
	data.envp = envp;
	if (!envp[0])
		data.envp = NULL;
	init_history(history);
	while (1)
	{
		input = readline("minishell > ");
		if (!input)
			break ;
		tokens = init_token(input);
		add_to_history(history, input);

		// Debugging : Afficher les tokens
		t_token *current = tokens;
		while (current)
		{
			printf("Token: %s, Type: %d\n", current->str, current->type); // Affiche le contenu du token
			current = current->next;
		}
		free(input);
	}
	close(history->fd);
	clear_history();
}
