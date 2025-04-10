/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:21:16 by humontas          #+#    #+#             */
/*   Updated: 2025/04/10 12:08:49 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	quote_checker(char *str)
{
	int	i;
	int	double_quote;
	int	single_quote;

	i = 0;
	double_quote = 0;
	single_quote = 0;
	while (str && str[i])
	{
		if (str[i] == '"')
			double_quote++;
		else if (str[i] == '\'')
			single_quote++;
		i++;
	}
	if (double_quote % 2 != 0 || single_quote % 2 != 0)
	{
		print_syntax_error(4, NULL);
		return (1);
	}
	return (0);
}

static int	parenthesis_checker(char *str)
{
	int	i;
	int	first_parenthesis;
	int	second_parenthesis;

	i = 0;
	first_parenthesis = 0;
	second_parenthesis = 0;
	while (str && str[i])
	{
		if (str[i] == '(')
			first_parenthesis++;
		else if (str[i] == ')')
			second_parenthesis++;
		i++;
	}
	if (first_parenthesis != second_parenthesis)
	{
		print_syntax_error(3, NULL);
		return (1);
	}
	return (0);
}

int	check_syntax_error(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == PIPE && (!curr->next || curr->next->type == PIPE))
			return (print_syntax_error(1, "|"));
		if (curr->type == IN || curr->type == OUT
			|| curr->type == APPEND || curr->type == HEREDOC)
		{
			if (!curr->next)
				return (print_syntax_error(2, NULL));
			if (curr->next->type != REDIR)
				return (print_syntax_error(1, curr->next->str));
		}
		curr = curr->next;
	}
	return (0);
}

int	init_parsing(char *str, t_token *tokens)
{
	if (quote_checker(str))
		return (1);
	if (parenthesis_checker(str))
		return (1);
	if (check_syntax_error(tokens))
		return (1);
	return (0);
}
