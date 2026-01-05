/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7.2.expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:31:01 by aidarsharaf       #+#    #+#             */
/*   Updated: 2026/01/04 15:05:44 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_get_var_name_len(char *arg)
{
	size_t	len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	return (len);
}

bool	ft_is_valid_var_char(int c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

char	*ft_expand_env_var(t_shell *shell, char *str)
{
	char	*var_name;
	char	*var_value;
	int		i;

	i = 1;
	while (str[i] && ft_is_valid_var_char(str[i]) == true)
		i++;
	var_name = ft_substr(str, 1, i - 1);
	if (!var_name)
		return (NULL);
	var_value = ft_getenv(shell->env, var_name);
	free(var_name);
	if (var_value)
		return (ft_strdup(var_value));
	else
		return (ft_strdup(""));
}

char	*ft_expand_dquotes_str(t_shell *shell, char *str, size_t len)
{
	char	*without_quotes;
	char	*expanded_str;

	without_quotes = ft_substr(str, 1, len - 2);
	if (!without_quotes)
		return (NULL);
	if (without_quotes[0] && without_quotes[0] == '$')
	{
		if (without_quotes[1] == '\0')
			return (free(without_quotes), ft_strdup("$"));
		if (without_quotes[1] == '?')
			expanded_str = ft_itoa(shell->exit_status);
		else if (without_quotes[1] == '$')
			expanded_str = ft_itoa(shell->shell_pid);
		else if (without_quotes[1] && ft_is_valid_var_char(without_quotes[1]))
			expanded_str = ft_expand_env_var(shell, without_quotes);
		else
			expanded_str = ft_strdup("");
		return (free(without_quotes), expanded_str);
	}
	else
		return (without_quotes);
}
