/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:15:05 by humontas          #+#    #+#             */
/*   Updated: 2025/03/25 13:56:35 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	main(void)
// {
// 	t_history	*history;
// 	t_minishell	*data;	
// 	char		*input;

// 	data = malloc(sizeof(t_minishell));
// 	if (!data)
// 		exit_error("minishell: Memory allocation failed\n", 1);
// 	history = malloc(sizeof(t_history));
// 	if (!history)
// 		exit_error("minishell: Memory allocation failed\n", 1);
// 	init_history(history);
// 	while (1)
// 	{
// 		input = readline("minishell > ");
// 		if (!input)
// 			break ;
// 		init_parsing(input);
// 		init_token(input);
// 		add_to_history(history, input);
// 		free(input);
// 	}
// 	close(history->fd);
// 	clear_history();
// }

void print_tokens(t_token *tokens)
{
	t_token *current = tokens;
	while (current)
	{
		printf("Token: %s, Type: %d\n", current->str, current->type);
		current = current->next;
	}
}

int main(void)
{
	t_history	*history;
	t_token		*tokens;
	char		*input;
	char		*prompt;

	prompt = ft_strjoin(getcwd(NULL, 0), "$ ");
	if (!prompt)
		exit_error("minishell: Memory allocation failed\n", 1);
	history = malloc(sizeof(t_history));
	if (!history)
		exit_error("minishell: Memory allocation failed\n", 1);
	init_history(history);
	while (1)
	{
		input = readline(prompt);
		if (!input)
			break ;
		init_parsing(input);
		tokens = init_token(input);
		print_tokens(tokens);  
		add_to_history(history, input);
		free(input);
	}
	free(prompt);
	close(history->fd);
	clear_history();
}
