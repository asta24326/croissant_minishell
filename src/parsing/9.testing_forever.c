/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9.testing_forever.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:49:03 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/09 19:16:40 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	if (c == 32 || c == 9)
		return (1);
	return (0);
}

// works
// checks whether c is pipe, right or left arrow
int	is_operator(char c)
{
	if (c == 124 || c == 60 || c == 62)
		return (1);
	return (0);
}

// works
// checks whether c is right or left arrow
int	is_redir(char c)
{
	if (c == 60 || c == 62)
		return (1);
	return (0);
}

// works
// checks whether c is double or single quotation mark
int	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

// works
// checks whether c is cmd/arg/flag/filename/delimiter
int	is_other(char c)
{
	if (is_whitespace(c) || is_operator(c) || is_quote(c))
		return (0);
	return (1);
}

int	are_closed_quotes(char *copy)
{
	char	quot_mark;

	quot_mark = 0;
	while (*copy)
	{
		if (is_quote(*copy) & !quot_mark)
			quot_mark = *copy;
		else if (*copy == quot_mark)
			quot_mark = 0;
		copy++;
	}
	if (quot_mark == 0)
		return (true);
	return (false);
}

int	are_valid_pipes(char *copy)
{
	int	flag;

	flag = 0;
	while (*copy)
	{
		if (is_quote(*copy) || is_redir(*copy) || is_other(*copy))
			flag = 1;
		else if (*copy == 124)
		{
			if (flag == 0)
				return (printf("Syntax error. Missing command/redir.\n"), false);
			flag = 0;
		}
		copy++;
	}
	return (true);
}

int	are_valid_redirs(char *copy)
{
	int		i;

	i = -1;
	while (copy[++i])
	{
		if (is_redir(copy[i]))
		{
			printf("arrow = %c\n", copy[i]);
			i++;
			if (copy[i] == copy[i - 1]) //case: double arrow
				i++;
			while (is_whitespace(copy[i]))
				i++;
			if (is_quote(copy[i]) && !is_quote(copy[i + 1])) //case:quoted filename/delimiter
				i++;
			if (!is_other(copy[i])) //MUST be other
				return (printf("Syntax error. Invalid redir(s).\n"), false);
		}
	}
	return (true);
}

int	main(void)
{
	// printf("quotes: %i\n", are_closed_quotes("hello!! 'hi''''''''' 'who is this?'"));
	// printf("pipes: %i\n", are_valid_pipes("|hello | and now? | no no no |"));
	printf("redirs: %i\n", are_valid_redirs(">file1    >>file <    'ghj'   <<      END"));
}
