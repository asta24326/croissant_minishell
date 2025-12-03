/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7.playground.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:24:38 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/03 19:34:32 by kschmitt         ###   ########.fr       */
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
int	is_token(char c)
{
	if (c == 124 || c == 60 || c == 62)
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
// checks whether c is '$' (prefix for env. arg.) or '-' (prefix for flag)
int	is_prefix(char c)
{
	if (c == 36 || c == 45)
		return (1);
	return (0);
}

// checks whether c is cmd/arg/flag/filename/delimiter
int	is_other(char c)
{
	if (is_whitespace(c) || is_token(c) || is_quote(c))
		return (0);
	return (1);
}

//----------------------------------------------------------

// ------------needs to go out---------------------
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	char	*dest;
	size_t	i;

	i = 0;
	s_len = ft_strlen(s);
	dest = (char *)malloc(sizeof(char) * (s_len + 1));
	if (dest == NULL)
		return (NULL);
	while (s_len > i)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	str_len;
	size_t	i;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	if (len > str_len - start)
		len = str_len - start;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (len > i)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
// ------------END (needs to go out)---------------------

// returns length of cmd/flag/arg/env_arg
int	get_arg_len(char *str)
{
	int	len;

	len = 0;
	while (!is_whitespace(*str) && !is_token(*str))
	{
		len++;
		str++;
	}
	return (len);
}

// loops through cmd/flag/arg/env_arg and returns index after quote
// int	parse_cmd(char *str, t_shell *minishell)
int	parse_cmd(char *str)
{
	int		index;
	char	*arg;

	index = get_arg_len(str);
	printf("%i\n", index);
	arg = ft_substr(str, 0, index); // attention: memory allocation
	printf("%s\n", arg);
// >> add it to char **args
	return (index);
}


int	main(void)
{
	parse_cmd("hello3.<($ARG>file   hey");
}
