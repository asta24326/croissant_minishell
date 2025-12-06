/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 22:27:14 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/12/04 06:27:47 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_expand_all_vars(t_shell *shell)// main function to expand variables in all commands
{
	t_cmd	*curr_cmd;
	int		i;

	curr_cmd = shell->cmd;
	while (curr_cmd)
	{
		i = -1;
		while (curr_cmd->args && curr_cmd->args[++i])// got through every coommand in list
			curr_cmd->args[i] = ft_expand_arg(shell, curr_cmd->args[i]);
		curr_cmd = curr_cmd->next;
	}
	return (SUCCESS);
}

char *ft_expand_arg(t_shell *shell, char *arg)
{
	char	*result;
	int		i;
	bool	in_qts;

	result = ft_strdup("");
	i = -1;
	in_qts = false;
	while (arg[++i])
	{
		if (arg[i] == '\'')// toogle single quote state
		{
			in_qts = !in_qts;
			continue ;// skip the quote character
		}
		if (arg[i] == '$' && arg[i+1] && in_qts == false)
			result = ft_handle_dollar(shell, arg, result, &i);
		else
			result = ft_append_char(arg[i], result);
	}
	free(arg);
	return (result);
}

char *ft_handle_dollar(t_shell *shell, char *arg, char *result, int *i)
{
	size_t	var_len;

	(*i)++;
	if (arg[*i] == '{')
		return (ft_handle_braces(shell, arg, result, *i));
	else if (arg[*i] == '?')
		return (ft_expand_question(shell, arg, result, *i));
	else if (arg[*i] == '$')
		return (ft_expand_pid(shell, arg, result, *i));
	else
		return (ft_expand_env_var(shell, arg, result, *i));
	return (NULL);
}

char *ft_handle_braces(t_shell *shell, char *arg, char *result, int *i)
{
	size_t	var_len;

	(*i)++; 
	while (!(arg[*i] == '}' || arg[*i] == '='))
		(*i)++;
	var_len = (*i);


}

bool	ft_is_valid_var_name(char *var, size_t var_len)
{
	int	i;

	if (!var || var_len == 0)
		return (false);
	if (var[0] != '_' && !ft_is_alpha(var[0]))//first char: letter or underscore
		return (false);
	i = 0;
	while (++i < var_len)//cheking the rest of the char
		if ((var[i] != '_') && !ft_isalnum(var[i]))
			return (false);
	return (true);
}

