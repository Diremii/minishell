/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:10:39 by humontas          #+#    #+#             */
/*   Updated: 2025/03/26 19:03:01 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_quote(char *input, size_t *i)
{
	if (*i > 0 && input[*i - 1] == '\\')
		return ;
	if (input[*i] == '\"')
	{
		(*i)++;
		while (input[*i] && input[*i] != '\"')
		{
			(*i)++;
			if (input[*i] && input[*i] == '\\' && input[*i + 1] != '\"')
				(*i) += 2;
		}
	}
	else if (input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] && input[*i] != '\'')
		{
			(*i)++;
			if (input[*i] && input[*i] == '\\' && input[*i + 1] != '\'')
				(*i) += 2;
		}
	}
}

char	**cut_quote_n_backslash(char *str) //TODO: parsing backslash
{
	size_t	i;
	size_t	j;
	char	**strs;

	i = 0;
	j = 0;
	while (str[i])
	{
		
		i++;
	}
}

char	*get_flag(char *input, size_t *i)
{
	size_t	j;
	char	*tmp;
	char	*str;
	char	**strs;

	j = *i;
	while (input[*i] && input[*i] != ' ')
	{
		skip_quote(input, i);
		(*i)++;
	}
	str = ft_substr(input, j, *i - j);
	strs = ft_split(str, '\"');
	j = 0;
	while (strs[j])
		j++;
	tmp = str;
	str = ft_join(strs, "", j);
	free_all(strs);
	free(tmp);
	return (str);
}

void	handle_command(char *input, size_t *i, t_token **tokens, t_data **data)
{
	char	*flag;
	
	if (!input[*i])
		return ;
	flag = get_flag(input, i);
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
		add_token_to_list(tokens, flag, ARG);
	}
}
