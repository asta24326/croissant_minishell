/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.3.prepare_redirs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:56:50 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/15 19:25:40 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	prepare_redirs(char *cmd_str, t_cmd *cmd)
{
	t_redirs	*redirects;

	redirects = (t_redirs *)malloc(sizeof(t_redirs));
	if (!redirects)
		return (printf("Memory allocation failed.\n"), FAILURE);
	redirects->list = ft_calloc(cmd->redirs_count + 1, sizeof(char *));
	if (!redirects->list)
		return (printf("Memory allocation failed.\n"), FAILURE);
	redirects->in_fd = 0;
	redirects->out_fd = 0;
	redirects->hdoc_delim = NULL;
	redirects->exp_hdoc = NULL; //needed?
	cmd->redirs = redirects;
	return (SUCCESS);
}
