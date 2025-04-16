/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:54:34 by okaname           #+#    #+#             */
/*   Updated: 2025/04/16 21:41:31 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	error_open_b(char *file)
{
	ft_putstr_fd("bash: ", 2);
	perror(file);
	return (1);
}

static int	open_infile_normant(char *infile, int *fd_in)
{
	if (*fd_in != 0)
		close(*fd_in);
	if (access(infile, F_OK) == -1 || access(infile, R_OK) == -1)
	{
		ft_putstr_fd("bash: ", 2);
		perror(infile);
		return (1);
	}
	*fd_in = open(infile, O_RDONLY);
	if (*fd_in == -1)
	{
		ft_putstr_fd("bash: ", 2);
		perror(infile);
		return (1);
	}
	return (0);
}

static int	open_file(char *file, int *fd_out, int open_type)
{
	if (*fd_out != 1)
		close(*fd_out);
	if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
	{
		ft_putstr_fd("bash: ", 2);
		perror(file);
		return (1);
	}
	if (open_type == 4)
	{
		*fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*fd_out == -1)
			return (error_open_b(file));
	}
	else if (open_type == 5)
	{
		*fd_out = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (*fd_out == -1)
			return (error_open_b(file));
	}
	return (0);
}

static char	*can_acsses(char *infile, int *last_in)
{
	*last_in = REDIR_IN;
	if (access(infile, F_OK) == -1 || access(infile, R_OK) == -1)
	{
		ft_putstr_fd("bash: ", 2);
		perror(infile);
		return (NULL);
	}
	return (infile);
}

int	set_fd_b(t_command *cmd, t_token **token)
{
	int		i;
	int		last_in;
	char	*openfile;

	i = -1;
	last_in = 0;
	while ((token[++i])->type != TOK_NULL)
	{
		if ((token[i])->type == TOK_REDIR_IN)
		{
			openfile = can_acsses((token[i + 1])->value, &last_in);
			if (openfile == NULL)
				return (1);
		}
		else if ((token[i])->type == TOK_HEREDOC)
			last_in = HERE_DOC;
		else if (((token[i])->type == 4 || (token[i])->type == 5)
			&& open_file((token[i + 1])->value, &(cmd->fd_out),
				(token[i])->type) == 1)
			return (1);
	}
	if (last_in == REDIR_IN && open_infile_normant(openfile,
			&(cmd->fd_in)) == 1)
		return (1);
	return (0);
}
