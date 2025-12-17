/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.1.main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:34:19 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/17 16:34:25 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell	*minishell;

	(void)ac;
	(void)av;
	minishell = (t_shell *)malloc(sizeof(t_shell));
	if (!minishell)
		return (perror("t_shell memory allocation"), FAILURE);
	// minishell->env = ft_env_dup(env);
	init_minishell(minishell); //what if this goes wrong? - fall out of loop
	end_minishell(minishell);
	return (0);
}
