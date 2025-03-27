/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:10:39 by humontas          #+#    #+#             */
/*   Updated: 2025/03/27 13:43:45 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_quote(char *input, size_t *i)
{
	if (input[*i] == '\"')
	{
		(*i)++;
		while (input[*i] && input[*i] != '\"')
			(*i)++;
	}
	else if (input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] && input[*i] != '\'')
			(*i)++;
	}
}

char	*get_flag(char *input, size_t *i)
{
	size_t	j;
	char	*str;

	j = *i;
	while (input[*i] && input[*i] != ' ')
	{
		skip_quote(input, i);
		(*i)++;
	}
	str = ft_substr(input, j, *i - j);
	if (!str)
		return (NULL);
	str = cut_quote(str);
	if (!str)
		return (NULL);
	j = 0;
	return (str);
}

void	handle_command(char *input, size_t *i, t_token **tokens, t_data **data)
{
	char	*flag;
	
	if (!input[*i])
		return ;
	flag = get_flag(input, i);
	if (!flag)
		return ;
	add_token_to_list(tokens, path_of(flag, (**data).envp), CMD);
	free(flag);
	if (!input[*i - 1])
		return ;
	while (input[*i] || !is_opperator(input[*i]))
	{
		while (input[*i] && input[*i] == ' ' && !is_opperator(input[*i]))
			(*i)++;
		if (!input[*i] || is_opperator(input[*i]))
			return ;
		flag = get_flag(input, i);
		if (!flag)
			return ;
		add_token_to_list(tokens, flag, ARG);
	}
}
