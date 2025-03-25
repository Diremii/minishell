/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:55:00 by humontas          #+#    #+#             */
/*   Updated: 2025/03/25 12:50:50 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(char *input, t_token_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->str = ft_strdup(input);
	if (!new_token->str)
		{
			free(new_token);
			return (NULL);
		}
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

t_token	*add_token_to_list(t_token **head, char *str, t_token_type type)
{
	t_token	*new_token;
	t_token	*current;

	new_token = create_token(str, type);
	if (!new_token)
		return (NULL);
	if (!*head)
	{
		*head = new_token;
		return (new_token);
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
	return (*head);
}

int	handle_operators(char *input, size_t i, t_token **tokens)
{
	if (!input)
		return (0);
	if (input[i] == '<' && input[i + 1] == '<')
		return (add_token_to_list(tokens, "<<", HEREDOC), 1);
	if (input[i] == '>' && input[i + 1] == '>')
		return (add_token_to_list(tokens, ">>", APPEND), 1);
	if (input[i] == '<')
		return (add_token_to_list(tokens, "<", INPUT), 1);
	if (input[i] == '>')
		return (add_token_to_list(tokens, ">", TRUNC), 1);
	if (input[i] == '|')
		return (add_token_to_list(tokens, "|", PIPE), 1);
	return (0);
}

t_token	*init_token(char *input)
{
	size_t		i;
	size_t		len_input;
	t_token		*tokens;

	i = 0;
	tokens = NULL;
	len_input = ft_strlen(input);
	while (input && i < len_input)
	{
		while (input[i] == ' ')
			i++;
		if (handle_operators(input, i, &tokens))
		{
			if ((input[i] == '<' && input[i + 1] == '<') || (input[i] == '>' && input[i + 1] == '>'))
				i += 2;
			else
				i++;
			continue;
		}
		else if (!input[i] || handle_cmd(input, &i, &tokens))
			continue;
		i++;
	}
	return (tokens);
}

