/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovietguy <sovietguy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:55:00 by humontas          #+#    #+#             */
/*   Updated: 2025/04/19 19:36:27 by sovietguy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*create_token(char *input, t_token_type type)
{
	t_token	*new_token;

	if (!input)
		return (NULL);
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

	if (!str)
		return (NULL);
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

t_token	*init_token(char *input, t_data *data)
{
	size_t	i;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	input = replace_dollar_in_str(input, data);
	while (input && input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		handle_operator(input, &i, &tokens);
		handle_command(input, &i, &tokens);
	}
	free(input);
	return (tokens);
}
