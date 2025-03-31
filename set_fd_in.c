/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 01:12:01 by okaname           #+#    #+#             */
/*   Updated: 2025/04/01 03:53:06 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(char *infile, int *fd_in)
{
	if (*fd_in == -1)
		return (-1);
	if (*fd_in != 0 && close(*fd_in) == -1)
		return (-1);
	*fd_in = open(infile, O_RDONLY);
	if (*fd_in == -1)
	{
		error_infile_open_failed(infile);
		return (-1);
	}
	return (1);
}

static char	*can_access(char *infile, bool *error_flag, char *open_file,
		int *last)
{
	*last = REDIR_IN;
	if (*error_flag)
		return (open_file);
	if (access(infile, F_OK) == -1 || access(infile, R_OK) == -1)
		*error_flag = true;
	return (infile);
}

int	set_fd_in(t_command **cmd, t_token **token)
{
	int		i;
	int		pipe_count;
	char	*open_file;
	bool	error_flag;
	int		last_in;

	i = 0;
	pipe_count = 0;
	error_flag = false;
	open_file = NULL;
	last_in = 0;
	cmd[pipe_count]->fd_in = 0;
	while (1)
	{
		if ((token[i])->type == TOK_PIPE || (token[i])->type == TOK_NULL)
		{
			if (error_flag)
				error_infile_open_failed(open_file);
			if (last_in == REDIR_IN)
				open_infile(open_file, &(cmd[pipe_count]->fd_in));
			if ((token[i])->type == TOK_NULL)
				break ;
			pipe_count++;
			cmd[pipe_count]->fd_in = 0;
		}
		else if ((token[i])->type == TOK_REDIR_IN)
			open_file = can_access((token[i + 1])->value, &error_flag,
					open_file, &last_in);
		else if ((token[i])->type == TOK_HEREDOC)
			here_doc((token[i + 1])->value, &last_in,
				&(cmd[pipe_count]->fd_in));
		i++;
	}
	return (0);
}
