/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:39:49 by humontas          #+#    #+#             */
/*   Updated: 2025/03/27 12:53:18 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_redirection(char *input, size_t *i, t_token **tokens)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			add_token_to_list(tokens, "<<", HEREDOC);
			(*i)++;
		}
		else
			add_token_to_list(tokens, "<", IN);
		(*i)++;
		redirection_file_handling(input, *tokens, i);
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			add_token_to_list(tokens, ">>", APPEND);
			(*i)++;
		}
		else
			add_token_to_list(tokens, ">", OUT);
		(*i)++;
		redirection_file_handling(input, *tokens, i);
	}
}

static void	handle_pipe(char *input, size_t *i, t_token **tokens)
{
	if (input[*i] == '|')
	{
		add_token_to_list(tokens, "|", PIPE);
		(*i)++;
	}
}

void	handle_operator(char *input, size_t *i, t_token **tokens)
{
	handle_redirection(input, i, tokens);
	handle_pipe(input, i, tokens);
}