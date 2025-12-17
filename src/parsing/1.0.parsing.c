/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.0.parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:29:02 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/15 18:15:36 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
// returns copy of the input str all bytes within quotes set to 0
char	*blackout_quoted_content(char *str)
{
	char	*copy;
	char	quot_mark;
	int		i;

	copy = ft_strjoin("", str);
	quot_mark = 0;
	i = -1;
	while (copy[++i])
	{
		if (is_quote(copy[i]))
		{
			quot_mark = copy[i];
			i++;
			while (copy[i + 1] && copy[i] != quot_mark)
			{
				copy[i] = 48;
				i++;
			}
		}
	}
	return (copy);
}

void	parse(char *pipeline, t_shell *minishell)
{
	char	*copy;

	copy = blackout_quoted_content(pipeline);
	if (!is_valid_syntax(copy))
		return (free(copy), FAILURE);
	parse_pipeline(copy, minishell);
	free(copy);
	parse_cmd_lines(pipeline, minishell->pipe_count + 1, minishell);
	execute(minishell);
}
