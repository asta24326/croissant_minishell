/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asharafe <asharafe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:33:41 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/28 13:31:27 by asharafe         ###   ########.fr       */
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
		return (ft_putstr_fd("parse_cmd_line", 2), FAILURE);
	create_cmd_list(arr, cmd_count, minishell);
	head = minishell->cmd;
	i = -1;
	while (++i < cmd_count)
	{
		if (!ft_process_cmd(minishell, arr[i]))
			return (ft_free_arr(arr), FAILURE);
		minishell->cmd = minishell->cmd->next;
	}
	minishell->cmd = head;
	return (ft_free_arr(arr), SUCCESS);
}

static int	ft_process_cmd(t_shell *minishell, char *cmd_str)
{
	if (!tokenize(cmd_str, minishell->cmd)
		|| !cleanup_quotes(minishell->cmd->args))
		return (FAILURE);
	ft_handle_heredoc(minishell, minishell->cmd);
	ft_expand(minishell);
	minishell->cmd->builtin = is_builtin_cmd(minishell->cmd);
	if (minishell->cmd->redirs_count > 0)
		if (!cleanup_quotes(minishell->cmd->redirs->list)
			|| !handle_redirs(minishell->cmd))
			return (FAILURE);
	return (SUCCESS);
}
