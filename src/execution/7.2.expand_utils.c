/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7.2.expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:31:01 by aidarsharaf       #+#    #+#             */
/*   Updated: 2026/01/05 17:58:25 by kschmitt         ###   ########.fr       */
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
	if (str[i - 1] == '"')
		var_name = ft_substr(str, 1, i - 2);
	else
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

char	*ft_expand_dquotes_str(t_shell *shell, char *str)
{
	char	*expanded_str;
	char	*result;

	if (str[1] == '$')
	{
		if (str[2] == '"')
			return (ft_strdup("$"));
		if (str[2] == '?')
			expanded_str = ft_itoa(shell->exit_status);
		else if (str[2] == '$')
			expanded_str = ft_itoa(shell->shell_pid);
		else if (str[2] && ft_is_valid_var_char(str[2]))
			expanded_str = ft_expand_env_var(shell, &str[1]);
		else
			expanded_str = ft_strdup("");
		result = ft_patch_with_dquotes(expanded_str);
		return (free(expanded_str), result);
	}
	else
		return (ft_strdup(str));
}

char	*ft_patch_with_dquotes(char *str)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin("\"", str);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, "\"");
	if (!result)
		return (free(temp), NULL);
	free(temp);
	return (result);
}
