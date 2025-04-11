/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:39:49 by humontas          #+#    #+#             */
/*   Updated: 2025/04/11 13:58:27 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_redirection(char *input, size_t *i, t_token **tokens, t_data *data)
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
		redirection_file_handling(input, *tokens, i, data);
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
		redirection_file_handling(input, *tokens, i, data);
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

void	handle_operator(char *input, size_t *i, t_token **tokens, t_data *data)
{
	handle_redirection(input, i, tokens, data);
	handle_pipe(input, i, tokens);
}
