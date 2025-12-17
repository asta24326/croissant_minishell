/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.1.parse_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:49:19 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/15 19:10:53 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ------------needs to go out---------------------
// size_t	ft_strlen(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (*s++)
// 		i++;
// 	return (i);
// }

// char	*ft_strdup(const char *s)
// {
// 	size_t	s_len;
// 	char	*dest;
// 	size_t	i;

// 	i = 0;
// 	s_len = ft_strlen(s);
// 	dest = (char *)malloc(sizeof(char) * (s_len + 1));
// 	if (dest == NULL)
// 		return (NULL);
// 	while (s_len > i)
// 	{
// 		dest[i] = s[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*dest;
// 	size_t	str_len;
// 	size_t	i;

// 	if (!s)
// 		return (NULL);
// 	str_len = ft_strlen(s);
// 	if (start >= str_len)
// 		return (ft_strdup(""));
// 	if (len > str_len - start)
// 		len = str_len - start;
// 	dest = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!dest)
// 		return (NULL);
// 	i = 0;
// 	while (len > i)
// 	{
// 		dest[i] = s[start + i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }
// ------------END (needs to go out)---------------------

// works
// returns length of cmd/flag/arg/env_arg
int	get_arg_len(char *str)
{
	int	len;

	len = 0;
	while (*str && !is_whitespace(*str) && !is_operator(*str))
	{
		len++;
		str++;
	}
	return (len);
}

// works
// includes the cmd/flag/arg/env_arg into the args_array
// attention, this will be called repeatedly as soon as arg is encountered
void	fill_args_arr(char *arg, t_cmd *cmd)
{
	static int	i; // needed because of repeated call

	cmd->args[i] = arg;
	i++;
	if (i == cmd->args_count) // NULL-terminate array and reset i to 0 when all cmds were handled
	{
		cmd->args[i] = NULL;
		i = 0;
	}
}

// works
// loops through cmd/flag/arg/env_arg and returns index after last byte
int	parse_cmd(char *cmd_str, t_cmd *cmd)
{
	int		index;
	char	*arg;

	index = get_arg_len(cmd_str);
	arg = ft_substr(cmd_str, 0, index); // attention: memory allocation
	fill_args_arr(arg, cmd);
	return (index);
}
