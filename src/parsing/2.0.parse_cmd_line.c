/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.0.parse_cmd_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:33:41 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/15 19:08:05 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_cmd_lines(char *pipeline, int cmd_count, t_shell *minishell)
{
	char	**arr;
	int		i;

	arr = ft_split(pipeline, 124);//splits the pipeline into its cmd-lines
	if (!arr)
		return (printf("Error while splitting pipeline.\n"), FAILURE);
	create_cmd_list(arr, cmd_count, minishell);
	clean(arr, cmd_count);
	i = -1;
	while (++i < cmd_count)
	{
		tokenize(minishell->cmd->args[i], minishell->cmd);
		handle_heredoc();
		expand_env_var();
		handle_quotes();
		handle_redirs();
	}
}
