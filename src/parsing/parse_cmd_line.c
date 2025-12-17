/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:33:41 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/17 17:54:28 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
// needed: error handling
int	parse_cmd_lines(char *pipeline, int cmd_count, t_shell *minishell)
{
	char	**arr;
	t_cmd	*head;
	int		i;

	arr = ft_split(pipeline, 124);//splits the pipeline into its cmd-lines
	if (!arr)
		return (perror("parse_cmd_line"), FAILURE);
	create_cmd_list(arr, cmd_count, minishell);
	head = minishell->cmd;
	i = -1;
	while (++i < cmd_count)
	{
		tokenize(arr[i], minishell->cmd);
		// handle_heredoc();
		// expand_env_var();
		cleanup_quotes(minishell->cmd->args);
		minishell->cmd->builtin = is_builtin_cmd(minishell->cmd);
		if (minishell->cmd->redirs_count > 0)
		{
			cleanup_quotes(minishell->cmd->redirs->list);
			handle_redirs(minishell->cmd);
		}
		minishell->cmd = minishell->cmd->next;
	}
	minishell->cmd = head;
	return (clean(arr, cmd_count), SUCCESS);
}
