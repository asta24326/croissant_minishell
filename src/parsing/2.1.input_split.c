/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.1.input_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:17:09 by kschmitt          #+#    #+#             */
/*   Updated: 2025/11/24 16:48:09 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libraries/libft/libft.h"

// ---------------  libft functions - need to go out!  --------------
static int	ft_strcount(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static int	ft_strlength(const char *s, char c)
{
	int		length;

	if (!ft_strchr(s, c))
		length = ft_strlen(s);
	else
	{
		length = 0;
		while (*s && *s == c)
			s++;
		while (*s && *s != c)
		{
			length++;
			s++;
		}
	}
	return (length);
}

static void	ft_free(char **arr_split)
{
	int	i;

	i = 0;
	while (arr_split[i])
	{
		free(arr_split[i]);
		i++;
	}
	free(arr_split);
}

static char	**ft_fillarr(char const *s, char c, char **arr_split)
{
	int		i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			arr_split[i] = ft_substr(s, 0, ft_strlength(s, c));
			if (!arr_split[i])
			{
				ft_free(arr_split);
				return (NULL);
			}
			s += ft_strlength(s, c);
			i++;
		}
	}
	arr_split[i] = NULL;
	return (arr_split);
}

char	**ft_split(char const *s, char c)
{
	char	**arr_split;

	if (s)
		arr_split = calloc((ft_strcount(s, c) + 1), sizeof(char *));
	if (!s || !arr_split)
		return (NULL);
	return (ft_fillarr(s, c, arr_split));
}
// ---------------  libft functions - end!  --------------

typedef struct s_cmd
{
	char	*cmd;
	char	**cmd_args;
	char	*infile;
	int		infile_fd;
	char	*outfile;
	int		outfile_fd;
	bool	append;
	char	*heredoc_delim;
	int		heredoc_fd;
	t_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	int		cmds_count;
	int		**pipes;
	t_cmd	*init_cmd;
}	t_data;

int	get_cmds_count(char **arr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arr[i] != NULL)
	{
		count++;
		i++;
	}
	return (count);
}

void	separate_cmds(t_data minishell, char *str)
{
	char	**cmd_arr;
	int		cmds

	cmd_arr = ft_split(str, 124);
	minishell.cmds_count = get_cmds_count(cmd_arr);
}


int	main(void)
{
	t_data	minishell;
	char	*input;

	printf("%i\n", minishell.cmds_count);
	input = "echo hi ha ho >file1 | echo hello | wc -l";
	separate_cmds(minishell, input);
	printf("%i\n", minishell.cmds_count);
}
