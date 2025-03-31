/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 01:12:26 by okaname           #+#    #+#             */
/*   Updated: 2025/04/01 03:58:10 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_appendfile(char *appendfile, int *fd_out)
{
	*fd_out = open(appendfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (*fd_out == -1)
		return (-1);
	return (*fd_out);
}

int	open_outfile(char *outfile, int *fd_out)
{
	*fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_out == -1)
		return (-1);
	return (*fd_out);
}

static char	*can_access(char *outfile, bool *error_flag, char *open_file)
{
	if (*error_flag)
		return (open_file);
	if (access(outfile, F_OK) == 0 || access(outfile, W_OK) == -1)
		*error_flag = true;
	return (outfile);
}

int	set_fd_out(t_command **cmd, t_token **token)
{
	int		i;
	int		pipe_count;
	char	*open_file;
	bool	error_flag;
	int		last_out;

	i = 0;
	pipe_count = 0;
	error_flag = false;
	open_file = NULL;
	last_out = 0;
	cmd[pipe_count]->fd_out = 1;
	while (1)
	{
		if ((token[i])->type == TOK_PIPE || (token[i])->type == TOK_NULL)
		{
			if (error_flag)
				error_infile_open_failed(open_file);
			if (last_out == REDIR_OUT)
				open_outfile(open_file, &(cmd[pipe_count]->fd_out));
			else if (last_out == APPEND)
				open_appendfile(open_file, &(cmd[pipe_count]->fd_out));
			if ((token[i])->type == TOK_NULL)
				break ;
			pipe_count++;
			cmd[pipe_count]->fd_out = 1;
		}
		else if ((token[i])->type == TOK_REDIR_OUT)
		{
			open_file = can_access((token[i + 1])->value, &error_flag,
					open_file);
			last_out = REDIR_OUT;
		}
		else if ((token[i])->type == TOK_REDIR_APPEND)
		{
			open_file = can_access((token[i + 1])->value, &error_flag,
					open_file);
			last_out = APPEND;
		}
		i++;
	}
	return (0);
}
