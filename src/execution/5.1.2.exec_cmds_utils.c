/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.1.2.exec_cmds_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asharafe <asharafe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:04:25 by asharafe          #+#    #+#             */
/*   Updated: 2026/01/02 23:13:05 by asharafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_wait_for_childs(t_shell *shell, int *status, int expected_childs)
{
	int		i;
	pid_t	pid;
	int		child_status;

	i = -1;
	while (++i < expected_childs)
	{
		pid = wait(&child_status);
		if (pid == -1)
		{
			ft_putstr_fd("wait failed", 2);
			break ;
		}
		if (pid == shell->last_pid)
		{
			if (WIFEXITED(child_status))
				shell->exit_status = WEXITSTATUS(child_status);
			else if (WIFSIGNALED(child_status))
				shell->exit_status = 128 + WTERMSIG(child_status);
		}
	}
	*status = child_status;
}
