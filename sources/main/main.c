/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:15:05 by humontas          #+#    #+#             */
/*   Updated: 2025/03/28 13:27:48 by ttremel          ###   ########.fr       */
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
		{
			free(tokens);
			break ;
		}
		tokens = init_token(input, &data);
		get_command(tokens, &data);
		add_to_history(history, input);

		// Debugging : show cmd content
		t_cmd	*tmp = data.cmd;
		size_t	i;
		
		while (tmp)
		{
			printf("Infile : %s\nOutfile : %s\nLimiter : %s\nHere_doc : %d\nAppend : %d\n", tmp->infile, tmp->outfile, tmp->limiter, tmp->here_doc, tmp->append);
			printf("args : ");
			i = 0;
			while (tmp->cmd_param && tmp->cmd_param[i])
			{
				printf("%s, ", tmp->cmd_param[i++]);
			}
			printf("\n");
			tmp = tmp->next;
		}
		// Debugging : Afficher les tokens
		// t_token *current = tokens;
		// while (current)
		// {
		// 	printf("Token: %s, Type: %d\n", current->str, current->type); // Affiche le contenu du token
		// 	current = current->next;
		// }
		clear_tokens(&tokens);
		cmd_clear(&data.cmd);
		free(input);
	}
	close(history->fd);
	free(history->last_command);
	free(history->path);
	free(history);
	clear_history();
}
