/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.3.parse_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:18:25 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/15 19:12:06 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
// returns length of redirection token
int	get_redir_len(char *str)
{
	int		len;
	char	*copy;

	len = 1; //skip the (first) redir sign
	copy = blackout_quoted_content(str);
	if (copy[len] == copy[len - 1]) //case: double arrow
		len++;
	while (is_whitespace(copy[len])) //case:whitespaces in between
		len++;
	while (!is_operator(copy[len]) && !is_whitespace(copy[len]))
		while (is_quote(copy[len]) || is_other(copy[len]))
			len++;
	free (copy);
	return (len);
}

void	fill_redirs_arr(char *redir, t_cmd *cmd)
{
	static int	i; // needed because of repeated call

	cmd->redirs->list[i] = redir;
	i++;
	if (i == cmd->redirs_count) // NULL-terminate array and reset i to 0 when all cmds were handled
	{
		cmd->redirs->list[i] = NULL;
		i = 0;
	}
}

// here, we look into single redirs
// returns index after the redir token
int	parse_redir(char *cmd_str, t_cmd *cmd)
{
	int		index;
	char	*redirect;

	index = get_redir_len(cmd_str);
	redirect = ft_substr(cmd_str, 0, index); // attention: memory allocation
	fill_redirs_arr(redirect, cmd);
	return (index);
}
