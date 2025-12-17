/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.2.handle_redirs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:05:38 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/16 14:17:26 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//attention: here, I need the index of the cmd
int	handle_outfile(char *filename, t_cmd *cmd)
{
	static int	fd;
	static int	cmd_index;

	if (cmd_index != cmd->index)//case: we arrived at next cmd
	{
		cmd_index = cmd->index;
		fd = 0;
	}
	if (fd > 0)//case:several outfiles in 1 cmd
		close (fd);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(filename), "Error while opening file\n");
	cmd->redirs->out_fd;
	free (filename);
	return (SUCCESS);
}

//attention: here, I need the index of the cmd
//attention: here, I need int append_fd in t_redirs
int	handle_append(char *filename, t_cmd *cmd)
{
	static int	fd;
	static int	cmd_index;

	if (cmd_index != cmd->index)//case: we arrived at next cmd
	{
		cmd_index = cmd->index;
		fd = 0;
	}
	if (fd > 0)//case:several appends in 1 cmd
		close (fd);
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror(filename), "Error while opening file\n");
	cmd->redirs->append_fd;
	free (filename);
	return (SUCCESS);
}

//attention: here, I need the index of the cmd
int	handle_infile(char *filename, t_cmd *cmd)
{
	static int	fd;
	static int	cmd_index;

	if (cmd_index != cmd->index)//case: we arrived at next cmd
	{
		cmd_index = cmd->index;
		fd = 0;
	}
	if (fd > 0)//case:several infiles in 1 cmd
		close (fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror(filename), "Error while opening file\n");
	cmd->redirs->in_fd;
	free (filename);
	return (SUCCESS);
}

//attention: here, I need the index of the cmd
// pre-condition: quotes were handled (aka eliminated)
// means: bool exp_hdoc was extracted while quote handling
int	handle_heredoc(char *filename, t_cmd *cmd)
{
	if (cmd->redirs->hdoc_delim != NULL)//case: multiple heredocs
	{
		free(cmd->redirs->hdoc_delim);
		cmd->redirs->hdoc_delim == NULL;
	}
	cmd->redirs->hdoc_delim = filename;
	return (SUCCESS);
}

// works
// returns the filename/delimiter
// pre-condition: quotes were handled (aka eliminated)
char	*get_filename(char *redir_str, int ops)
{
	int	i;
	int	len;
	int	whitespaces;

	i = ops - 1;//jump to last redir operator sign
	len = ft_strlen(redir_str);
	whitespaces = 0;
	while (is_whitespace(redir_str[++i]))
		whitespaces += 1;
	return (ft_substr(redir_str, ops + whitespaces, len - ops - whitespaces));
}

// works
// handles the redir depending on the type
int	handle_redir(char **redir_list, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (redir_list[++i])
	{
		if (redir_list[i][0] == '>' && redir_list[i][1] != '>')
			handle_outfile(get_filename(redir_list[i], 1), cmd);
		else if (redir_list[i][0] == '>' && redir_list[i][1] == '>')
			handle_append(get_filename(redir_list[i], 2), cmd);
		else if (redir_list[i][0] == '<' && redir_list[i][1] != '<')
			handle_infile(get_filename(redir_list[i], 1), cmd);
		// else if (redir_list[i][0] == '<' && redir_list[i][1] == '<')
		// 	handle_heredoc(get_filename(redir_list[i], strlen, 2), cmd);//done by Aidar
	}
	return (SUCCESS);
}
