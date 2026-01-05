/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9.1.2.heredoc_handle_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asharafe <asharafe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 20:18:43 by asharafe          #+#    #+#             */
/*   Updated: 2026/01/04 11:45:02 by asharafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_expand_heredoc_str(t_shell *shell, char *str)
{
	if (!str)
		return (NULL);
	if (str[0] == '$')
		return (ft_expand_dollar_start(shell, str));
	return (ft_strdup(str));
}
