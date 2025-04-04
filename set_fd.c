/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 01:50:03 by okaname           #+#    #+#             */
/*   Updated: 2025/04/05 02:21:34 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile_normant(char *infile, int *fd_in)
{
	if (*fd_in != 0 && close(*fd_in) == -1)
		return (error_close());
	if (access(infile, F_OK) == -1 || access(infile, R_OK) == -1)
		return (error_accese(infile));
	*fd_in = open(infile, O_RDONLY);
	if (*fd_in == -1)
		return (error_open(infile));
	return (1);
}

int	open_outfile(char *outfile, int *fd_out)
{
	*fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_out == -1)
		return (error_open(outfile));
	return (*fd_out);
}

int	open_appendfile(char *appendfile, int *fd_out)
{
	*fd_out = open(appendfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (*fd_out == -1)
		return (error_open(appendfile));
	return (*fd_out);
}

int	open_file(char *file, int *fd_out, int open_type)
{
	if (*fd_out != 1 && close(*fd_out) == -1)
		return (error_close());
	if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
		return (error_accese(file));
	if (open_type == 4)
		return (open_outfile(file, fd_out));
	else if (open_type == 5)
		return (open_appendfile(file, fd_out));
	return (1);
}

int	set_fd(t_command **cmd, t_token **token, int count)
{
	int	i;
	int	pipe_count;
	int	last_in;

	i = -1;
	pipe_count = 0;
	last_in = 0;
	(*cmd)->fd_in = 0;
	while ((token[++i])->type != TOK_NULL)
	{
		if ((token[i])->type == TOK_PIPE)
			pipe_count++;
		else if (pipe_count != count)
			continue ;
		else if ((token[i])->type == TOK_REDIR_IN
			&& open_infile_normant((token[i + 1])->value, &(*cmd)->fd_in) == -1)
			return (-1);
		else if ((token[i])->type == TOK_HEREDOC)
			last_in = HERE_DOC;
		else if (((token[i])->type == 4 || (token[i])->type == 5)
			&& open_file((token[i + 1])->value, &(*cmd)->fd_out,
				(token[i])->type) == -1)
			return (-1);
	}
	return (0);
}
