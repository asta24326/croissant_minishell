/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _print_parsing_results.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:32:56 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/18 17:55:13 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// goes out - only for testing
void	print_list(t_cmd *cmd, int cmd_count)
{
	int		i;
	int		j;
	t_cmd	*current;

	i = 0;
	current = cmd;

	printf("#cmd: %i\n", cmd_count);
	while (i < cmd_count)
	{
		printf("i: %i\n", i);
		printf("------------- ARG -------------\n");
		printf("index: %i\n", current->index);
		printf("tadaaaa (args): [%s]\n", current->args[0]);
		printf("is builtin: %i\n\n", current->builtin);
		j = 0;
		if (current->redirs != 0)
		{
			printf("------------ REDIR -------------\n");
			// while (current->redirs_count > 0)
			// {
			// 	printf("in here!\n");
			// 	printf("tadaaaa (redirs): %s\n", current->redirs->list[0]);
			// 	j++;
			// 	current->redirs_count--;
			// }
			printf("in_fd: %i\n", current->redirs->in_fd);
			printf("out_fd: %i\n", current->redirs->out_fd);
			// printf("append_fd: %i\n", current->redirs->append_fd);
			printf("hdoc_delim: [%s]\n", current->redirs->hdoc_delim);
			printf("exp_hdoc: %i\n\n\n", current->redirs->exp_hdoc);
		}
		current = current->next;
		i++;
	}
}
