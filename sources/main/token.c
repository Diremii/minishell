/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:55:00 by humontas          #+#    #+#             */
/*   Updated: 2025/03/24 16:14:36 by humontas         ###   ########.fr       */
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

int	handle_operators(char *input, int i, t_token **tokens)
{
	if (input[i] == '<' && input[i + 1] == '<')
		add_token_to_list(tokens, "<<", HEREDOC);
	else if (input[i] == '>' && input[i + 1] == '>')
		add_token_to_list(tokens, ">>", APPEND);
	else if (input[i] == '<')
		add_token_to_list(tokens, "<", INPUT);
	else if (input[i] == '>')
		add_token_to_list(tokens, ">", TRUNC);
	else if (input[i] == '|')
		add_token_to_list(tokens, "|", PIPE);
	else
		return (0);
	return (1);
}

void	handle_args(char *input, int i, t_token **tokens)
{
	int		start;
	char	*word;

	start = i;
	while (input[i] && input[i] != ' ' && input[i] != '<' && input[i] != '>' && input[i] != '|')
		i++;
	word = ft_substr(input, start, i - start);
	if (!word)
		return;
	add_token_to_list(tokens, word, ARG);
	free(word);
}

t_token	*init_token(char *input)
{
	int		i;
	char	*word;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	while (input && input[i] == ' ')
		i++;
	while (input && input[i])
	{
		if (handle_operators(input, i, &tokens))
			if ((input[i] == '<' && input[i + 1] == '<') || (input[i] == '>' && input[i + 1] == '>'))
				i += 2;
		else
			handle_args(input, i, &tokens);
		i++;
	}
	return (tokens);
}
