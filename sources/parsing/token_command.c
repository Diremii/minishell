/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:10:39 by humontas          #+#    #+#             */
/*   Updated: 2025/04/15 17:35:03 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_quote(char *input, size_t *i)
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

char	*get_flag(char *input, size_t *i, t_data *data)
{
	size_t	j;
	char	*str;

	(void)data;
	j = *i;
	while (input[*i] && input[*i] != ' ' && !is_opperator(input[*i]))
	{
		skip_quote(input, i);
		if (input[*i] == '\0')
			return (ft_strndup(input + j, *i - j));
		(*i)++;
	}
	str = ft_strndup(input + j, *i - j);
	if (!str)
		return (NULL);
	//str = replace_dolar_in_str(str, data);
	str = cut_quote(str);
	if (!str)
		return (NULL);
	return (str);
}

void	handle_args(char *input, size_t *i, t_token **tokens, t_data *data)
{
	char	*flag;

	flag = NULL;
	while (input[*i] || !is_opperator(input[*i]))
	{
		while (input[*i] && input[*i] == ' ' && !is_opperator(input[*i]))
			(*i)++;
		if (!input[*i] || is_opperator(input[*i]))
			return ;
		flag = get_flag(input, i, data);
		if (!flag)
			return ;
		add_token_to_list(tokens, flag, ARG);
		free(flag);
	}
}

void	handle_command(char *input, size_t *i, t_token **tokens, t_data *data)
{
	char	*flag;

	if (is_opperator(input[*i]))
		return ;
	flag = get_flag(input, i, data);
	if (!flag)
		return ;
	add_token_to_list(tokens, flag, CMD);
	free(flag);
	if (!input[*i - 1])
		return ;
	handle_args(input, i, tokens, data);
}
