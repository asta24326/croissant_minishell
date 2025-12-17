/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.2.prepare_args_arr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:37:46 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/15 19:09:29 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// // attention: this is double >> needs to go out here (or maybe use only once)
// // works
// // returns copy of the input str all bytes within quotes set to 0
// // attention: I do not handle non-closed quotes (as discussed)
// char	*blackout_quoted_content(char *str)
// {
// 	char	*copy;
// 	char	quot_mark;
// 	int		i;

// 	copy = ft_strjoin("", str);		//memory freed in get_pipe_count
// 	quot_mark = 0;
// 	i = 0;
// 	while (copy[i])
// 	{
// 		if (is_quote(copy[i]))
// 		{
// 			quot_mark = copy[i];
// 			i++;
// 			while (copy[i] && copy[i] != quot_mark)
// 			{
// 				copy[i] = 48;
// 				i++;
// 			}
// 		}
// 		i++;
// 	}
// 	return (copy);
// }

//works
// returns amout of redirs in 1 cmd_line
int	get_redir_count(char *copy)
{
	int		count;
	int		i;

	count = 0;
	i = -1;
	while (copy[++i])
	{
		if (is_redir(copy[i]))
		{
			count++;
			i++;
			if (is_redir(copy[i]))
				i++;
		}
	}
	return (count);
}

// works
// returns the amout of arguments in 1 cmd_line
int	get_arg_count(char *copy)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (copy[++i])
	{
		if (!is_whitespace(copy[i]) && !is_operator(copy[i]))
		{
			count++;
			while (copy[i] && !is_whitespace(copy[i]) // whitespace and operator work as delimiter
				&& !is_operator(copy[i]))
				i++;
		}
	}
	// if redirs in cmd_str, substract the filename/delimiter
	return (count - get_redir_count(copy));
}

// works, no memory leaks
// sets the arg_count and the args_arr for cmd node
void	prepare_args_arr(char *cmd_str, t_cmd *cmd)
{
	char	*copy;

	copy = blackout_quoted_content(cmd_str);
	cmd->args_count = get_arg_count(copy);
	cmd->redirs_count = get_redir_count(copy);
	free (copy);
	cmd->args = ft_calloc(cmd->args_count + 1, sizeof(char *)); //attention: memory allocation // calloc needed as single strings are not filled immediatly
}
