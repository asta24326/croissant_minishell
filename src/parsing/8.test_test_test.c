/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8.test_test_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:01:20 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/08 17:53:23 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	if (c == 32 || c == 9)
		return (1);
	return (0);
}

// works
// checks whether c is pipe, right or left arrow
int	is_operator(char c)
{
	if (c == 124 || c == 60 || c == 62)
		return (1);
	return (0);
}

// works
// checks whether c is double or single quotation mark
int	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

// works
// checks whether c is cmd/arg/flag/filename/delimiter
int	is_other(char c)
{
	if (is_whitespace(c) || is_operator(c) || is_quote(c))
		return (0);
	return (1);
}


// ---------------  libft functions - need to go out!  --------------
char	*ft_strdup(const char *s)
{
	int		i;
	char	*d;

	i = 0;
	d = malloc(strlen(s) + 1);
	if (!d)
		return (NULL);
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	const char	*ptr;

	ptr = src;
	if (size == 0)
		return (strlen(src));
	if (size != 0)
	{
		while (size > 1 && *src)
		{
			*dest++ = *src++;
			size--;
		}
		*dest = '\0';
	}
	return (strlen(ptr));
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	max;

	if (!s)
		return (NULL);
	max = strlen(s);
	if ((start >= max) || len == 0)
		return (ft_strdup(""));
	if (len > (size_t)strlen(s + start))
		len = (size_t)strlen(s + start);
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	s += start;
	if (start < max)
		ft_strlcpy(sub, s, len + 1);
	return (sub);
}

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

	if (!ft_strrchr(s, c))
		length = strlen(s);
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

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = strlen(dst);
	if (size <= i)
		return (size + strlen(src));
	j = 0;
	while (src[j] && ((i + j) < (size - 1)))
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (i + strlen(src));
}

// goes out
char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	len1 = strlen(s1);
	len2 = strlen(s2);
	new = (char *)calloc((len1 + len2 + 1), sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcat(new, s1, len1 + 1);
	ft_strlcat(new, s2, len2 + len1 + 1);
	return (new);
}

char	*blackout_quoted_content(char *str)
{
	char	*copy;
	char	quot_mark;
	int		i;

	copy = ft_strjoin("", str);		//memory freed in get_pipe_count
	quot_mark = 0;
	i = 0;
	while (copy[i])
	{
		if (is_quote(copy[i]))
		{
			quot_mark = copy[i];
			i++;
			while (copy[i] && copy[i] != quot_mark)
			{
				copy[i] = 48;
				i++;
			}
		}
		i++;
	}
	return (copy);
}

// ----------until here, everything goes out--------------


//works
// returns amout of redirs in 1 cmd_line
int	get_redir_count(char *copy)
{
	int		count;
	int		i;

	count = 0;
	i = -1;
	while (copy[++i])
	{
		// works because pipes have been taken out and quotes are blacked out
		if (is_operator(copy[i]))
		{
			count++;
			i++;
			if (is_operator(copy[i]))
				i++;
		}
	}
	return (count);
}

// works
// returns the amout of arguments in 1 cmd_line
int	get_arg_count(char *copy)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (copy[++i])
	{
		if (!is_whitespace(copy[i]) && !is_operator(copy[i]))
		{
			count++;
			// whitespace and operator work as delimiter
			while (copy[i] && !is_whitespace(copy[i])
				&& !is_operator(copy[i]))
				i++;
		}
	}
	// if redirs in cmd_str, substract the filename/delimiter
	return (count - get_redir_count(copy));
}

// works
// includes the cmd/flag/arg/env_arg into the args_array
// attention, this will be called repeatedly as soon as arg is encountered
void	fill_args_arr(char *arg_str, t_cmd *cmd)
{
	static int	i; // needed because of repeated call

	printf("i = %i\n", i);
	printf("#args = %i\n", cmd->args_count);
	printf("str passed to arr: %s\n", arg_str);
	cmd->args[i] = arg_str;
	i++;
	// NULL-terminate array and reset i to 0 when all cmds were handled
	if (i == cmd->args_count)
	{
		cmd->args[i] = NULL;
		i = 0;
	}
}


int	get_arg_len(char *str)
{
	int	len;

	len = 0;
	while (*str && !is_whitespace(*str) && !is_operator(*str))
	{
		len++;
		str++;
	}
	return (len);
}

// works
// loops through cmd/flag/arg/env_arg and returns index after quote
int	parse_cmd(char *str, t_cmd *cmd)
{
	int		index;
	char	*arg;

	index = get_arg_len(str);
	arg = ft_substr(str, 0, index); // attention: memory allocation
	fill_args_arr(arg, cmd);
	return (index);
}

int	get_quot_len(char *str, char quot_mark, int *env_arg)
{
	static int	i;
	static int	len;

	// skip first quotation mark
	i = 1;
	len = 0;
	// while (str[i] && str[i] != quot_mark)
	while ((str[i] && !is_whitespace(str[i]) && !is_operator(str[i])))
	{
		if (!is_quote(str[i]))
			len++;
		// if dollar is encountered, env_arg is "tunred off"
		if (str[i] == 36)
			*env_arg = 0;
		i++;
	}
	// adds two bytes in case of single quotation marks in combination with dollar sign to include quotation marks into string
	if (quot_mark == 39 && *env_arg == 0)
		len += 2;
	printf("len = %i\n", len);
	return (len);
}

int	get_full_quot_len(char *str, char quot_mark, int *env_arg)
{
	static int	i;
	static int	len;

	// skip first quotation mark
	i = 1;
	len = 0;
	// while (str[i] && str[i] != quot_mark)
	while ((str[i] && !is_whitespace(str[i]) && !is_operator(str[i])))
	{
		len++;
		// if dollar is encountered, env_arg is "tunred off"
		if (str[i] == 36)
			*env_arg = 0;
		i++;
	}
	// adds two bytes in case of single quotation marks in combination with dollar sign to include quotation marks into string
	if (quot_mark == 39 && *env_arg == 0)
		len += 2;
	printf("len = %i\n", len);
	return (len);
}

char	*ft_substr_quote(const char *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	max;
	int				i;
	int				j;

	printf("start = %i\n", start);
	printf("len = %zu\n", len);
	printf("str passed: %s\n", s);
	if (!s)
		return (NULL);
	max = strlen(s);
	if ((start >= max) || len == 0)
		return (ft_strdup(""));
	if (len > (size_t)strlen(s + start))
		len = (size_t)strlen(s + start);
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	s += start;
	if (start < max)
	{
		i = 0;
		j = 0;
		printf("in here\n");
		while (len > 0 && s[i])
		{
			if (!is_quote(s[i]))
			{
				printf("char in loop: %c\n", s[i]);
				sub[j] = s[i];
				len--;
				j++;
			}
			printf("len:%zu\n", len);
			printf("%i\n", i);
			i++;
		}
		sub[i] = '\0';
		printf("new arg wo quotes: %s\n", sub);
	}
	// 	ft_strlcpy(sub, s, len + 1);
	return (sub);
}

// works
// attention: so far not conisdered: open quotation marks
// loops through quotation and returns index after quote
int	parse_quote(char *str, t_cmd *cmd)
{
	int		env_arg;
	int		index;
	char	*quot;

	env_arg = 1; //true by default
	index = get_full_quot_len(str, *str, &env_arg);
	quot = ft_substr_quote(str, env_arg, get_quot_len(str, *str, &env_arg));		//attention: memory allocation
	printf("quot: %s\n", quot);
	fill_args_arr(quot, cmd);
	// add 2 bytes for 2 quotation marks
	if (*str == 34 || (*str == 39 && env_arg == 1))
		index += 2;
	return (index);
}

void	tokenize(char *cmd_str, t_cmd *cmd)
{
	// loops through cmd_str and sets i to byte after operator
	while (*cmd_str)
	{
		if (is_quote(*cmd_str) || is_other(*cmd_str))
			cmd_str += parse_cmd(cmd_str, cmd);
		// works because at this point, the pipe operators were taken out already
		else if (is_operator(*cmd_str))
		{
			printf("redir!\n");
			cmd_str += 6;
		}
			// cmd_str += parse_redir(cmd_str, cmd);
		else
			cmd_str += 1;
	}
}

// void	tokenize(char *cmd_str, t_cmd *cmd)
// {
// 	// int	i;
// 	// int	len;

// 	// i = 0;
// 	// len = strlen(cmd_str);
// 	// loops through cmd_str and sets i to byte after operator
// 	while (*cmd_str)
// 	{
// 		// printf("endless loop here\n");
// 		// printf("%c\n", *cmd_str);
// 		// cmd_str += 1;
// 		if (is_quote(*cmd_str))
// 		{
// 			// printf("is quote!\n");
// 			cmd_str += parse_quote(cmd_str, cmd);
// 			// printf("rest of string:%s\n", cmd_str);
// 		}
// 		// printf("i=%i\n", i);
// 		else if (is_other(*cmd_str))
// 		{
// 			// printf("is other!\n");
// 			cmd_str += parse_cmd(cmd_str, cmd);
// 			// printf("rest of string:%s\n", cmd_str);
// 		}
// 		// printf("i=%i\n", i);
// 		// // // works because at this point, the pipe operators were taken out already
// 		// // // if (is_operator(cmd_str[i]))
// 		// // // 	cmd_str += parse_redir(cmd_str + i, cmd);
// 		else
// 		// {
// 		// 	printf("i=%i\n", i);
// 		// 	printf("len=%i\n", len);
// 		// 	if (i > len)
// 		// 		cmd_str -= 1;
// 				// else
// 				// {
// 				// 	printf(" bef white: %c\n", cmd_str[i - 1]);
// 				// 	printf("white: %c\n", cmd_str[i]);
// 			cmd_str += 1;
// 		// }
// 	}
// }

// void	tokenize(char *cmd_str, t_cmd *cmd)
// {
// 	int	i;

// 	i = 0;
// 	// loops through cmd_str and sets i to byte after operator
// 	while (cmd_str[i])
// 	{
// 		if (is_quote(cmd_str[i]))
// 			cmd_str += parse_quote(cmd_str + i, cmd);
// 		if (is_other(cmd_str[i]))
// 			cmd_str += parse_cmd(cmd_str + i, cmd);
// 		// works because at this point, the pipe operators were taken out already
// 		// if (is_operator(cmd_str[i]))
// 		// 	cmd_str += parse_redir(cmd_str + i, cmd);
// 		else
// 			i++;
// 	}
// }

// works, no memory leaks
// sets the arg_count and the args_arr for cmd node
void	create_args_arr(char *cmd_str, t_cmd *cmd)
{
	char	*copy;

	copy = blackout_quoted_content(cmd_str);
	cmd->args_count = get_arg_count(copy);
	// calloc needed as single strings are not filled immediatly
	cmd->args = calloc(cmd->args_count + 1, sizeof(char *)); //attention: memory allocation
	free (copy);
	tokenize(cmd_str, cmd);
}

// works
// creates t_cmd node
t_cmd	*create_node(char *cmd_line)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (printf("Error with node creation.\n"), NULL);
	//extracts char **args and int args_count;
	create_args_arr(cmd_line, new);
	// new->builtin = is_builtin_cmd(cmd_line); //only when I identified cmd - TODO
	// new->redirs = extract_redir_data(cmd_line); //will be handled in parse_redir - TODO
	// printf("after node creation: %s\n", new->args[0]);
	new->next = NULL;
	return (new);
}

// works
// adds a new node to the back of the linked list
void	add_node(t_cmd **list, t_cmd *new)
{
	t_cmd	*head;

	head = *list;
	while (head != NULL && head->next != NULL)
		head = head->next;
	head->next = new;
}

// // goes out - only for testing
void	print_list(t_cmd *list)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		printf("i = %i\n", i);
		printf("tadaaaa: %s\n", list->args[0]);
		list = list->next;
		i++;
	}
}

// to be tested
// splits pipeline into cmd-lines, and creates 1 node per cmd-line
// attention: what I need here to be passed is blacked out string!
void	create_cmd_list(char *pipeline, int cmd_count, t_shell *minishell)
{
	char	**arr;
	t_cmd	*list;
	int		i;

	// splits the pipeline into its cmd-lines
	arr = ft_split(pipeline, 124); //memory allocation
	// initiates the list, creates first node with entire cmd line
	// printf("after split: %s\n", arr[3]);
	list = create_node(arr[0]);
	i = 0;
	// creates entire list by passing 1 cmd-line per node
	while (++i < cmd_count)
		add_node(&list, create_node(arr[i]));
	// print_list(list);
	minishell->cmd = list;
	//free arr here?
}



// ----------for testing only-----------------------
int	main(void)
{
	t_shell	minishell;
	int		i;

	i = 0;
	minishell.pipe_count = 3;
	create_cmd_list("hello string | 'another''hey' sk8ter | >file2 whoop whoop | END", minishell.pipe_count + 1, &minishell);
	printf("%s\n", minishell.cmd->args[0]);
	printf("%s\n", minishell.cmd->args[1]);
	minishell.cmd = minishell.cmd->next;
	printf("%s\n", minishell.cmd->args[0]);
	printf("%s\n", minishell.cmd->args[1]);
	printf("%s\n", minishell.cmd->args[2]);
	minishell.cmd = minishell.cmd->next;
	printf("%s\n", minishell.cmd->args[0]);
	minishell.cmd = minishell.cmd->next;
	printf("%s\n", minishell.cmd->args[0]);
	// while (i < 4)
	// {
	// 	printf("%s\n", minishell.cmd->args[i]);
	// 	i++;
	// 	minishell.cmd = minishell.cmd->next;
	// }
}
