/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.6.1.create_args_arr.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:37:46 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/03 19:46:56 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
// needed: str with blackout quotes
// needed: how many redirs? (also with blackout quotes)
int	get_arg_count(char *cmd_str)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (cmd_str[++i])
	{
		if (!is_whitespace(cmd_str[i]) && !is_token(cmd_str[i]))
		{
			count++;
			// whitespace and token work as delimiter
			while (cmd_str[i] && !is_whitespace(cmd_str[i])
				&& !is_token(cmd_str[i]))
				i++;
		}
	}
	// if redirs in cmd_str, substract the filename/delimiter
	return (count - (get_redir_count(cmd_str)));
}
