/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:10:39 by humontas          #+#    #+#             */
/*   Updated: 2025/03/25 18:32:35 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_opperator(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '\'' || c == '\"')
		return (1);
	return (0);
}

char	*get_flag(char *input, size_t **i)
{
	size_t	j;
	char	*cmd;
	char	*tmp;
	char	quote;

	j = **i;
	if (input[**i] == '\'' || input[**i] == '\"')
	{
		quote = '\'';
		if (input[**i] == '\"')
			quote = '\"';
		(**i)++;
		while (input[**i] && input[**i] != quote)
			(**i)++;
		cmd = ft_substr(input, j + 1, **i - j - 1);
		if (input[**i] && (input[**i] == '\"' || input[**i] == '\'')) //TODO : fix appending string
		{
			tmp = cmd;
			cmd = ft_strjoin(cmd, get_flag(input, i));
			free(tmp);
		}
		return (cmd);
	}
	while (input[**i] && input[**i] != ' ' && !is_opperator(input[**i]))
		(**i)++;
	cmd = ft_substr(input, j, **i - j);
	if (input[**i] && (input[**i] == '\"' || input[**i] == '\''))
	{
		tmp = cmd;
		cmd = ft_strjoin(cmd, get_flag(input, i));
		free(tmp);
	}
	return (cmd);
}

void	handle_command(char *input, size_t *i, t_token **tokens, t_data **data)
{
	char	*flag;
	
	flag = get_flag(input, &i);
	add_token_to_list(tokens, path_of(flag, (**data).envp), CMD);
	free(flag);
	while (input[*i] || !is_opperator(input[*i]))
	{
		while (input[*i] && input[*i] == ' ' && !is_opperator(input[*i]))
			(*i)++;
		if (!input[*i] || is_opperator(input[*i]))
			return ;
		flag = get_flag(input, &i);
		add_token_to_list(tokens, flag, ARG);
	}
}
