/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.4.minishell_termination.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:28:14 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/15 13:07:45 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	end_minishell(t_shell *minishell)
{
	free(minishell->prompt);
	free(minishell->env);
	free(minishell);
	minishell = NULL;
	rl_clear_history();
}
