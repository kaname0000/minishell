/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 01:50:03 by okaname           #+#    #+#             */
/*   Updated: 2025/04/16 21:31:08 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	open_infile_normant(char *infile, int *fd_in)
{
	if (*fd_in != 0)
		close(*fd_in);
	*fd_in = open(infile, O_RDONLY);
	if (*fd_in == -1)
		error_open(infile);
}

static void	open_file(char *file, int *fd_out, int open_type)
{
	if (*fd_out != 1)
		close(*fd_out);
	if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
		error_accese(file);
	if (open_type == 4)
	{
		*fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*fd_out == -1)
			error_open(file);
	}
	else if (open_type == 5)
	{
		*fd_out = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (*fd_out == -1)
			error_open(file);
	}
}

static char	*can_acsses(char *infile, int *last_in)
{
	*last_in = REDIR_IN;
	if (access(infile, F_OK) == -1 || access(infile, R_OK) == -1)
		error_accese(infile);
	return (infile);
}

int	set_fd(t_command **cmd, t_token **token, int count)
{
	int		i;
	int		pipe_count;
	int		last_in;
	char	*openfile;

	i = -1;
	pipe_count = 0;
	last_in = 0;
	while ((token[++i])->type != TOK_NULL)
	{
		if ((token[i])->type == TOK_PIPE)
			pipe_count++;
		else if (pipe_count != count)
			continue ;
		else if ((token[i])->type == TOK_REDIR_IN)
			openfile = can_acsses((token[i + 1])->value, &last_in);
		else if ((token[i])->type == TOK_HEREDOC)
			last_in = HERE_DOC;
		else if (((token[i])->type == 4 || (token[i])->type == 5))
			open_file((token[i + 1])->value, &(*cmd)->fd_out, (token[i])->type);
	}
	if (last_in == REDIR_IN)
		open_infile_normant(openfile, &(*cmd)->fd_in);
	return (0);
}
