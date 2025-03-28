/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:10:39 by humontas          #+#    #+#             */
/*   Updated: 2025/03/27 14:35:31 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_valid(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == ' ' || c == '\t')
		return (false);
	return (true);
}

void	redirection_file_handling(char *input, t_token *tokens, size_t *i)
{
	size_t	size;
	size_t	index;
	char	*word;

	index = 0;
	size = (*i);
	while (input[(*i)] == ' ' || input[(*i)] == '\t')
		(*i)++;
	while (input[size] && is_valid(input[(*i)]))
		size++;
	word = get_flag(input, i);
	if (!word)
		return ;
	add_token_to_list(&tokens, word, REDIR);
}
