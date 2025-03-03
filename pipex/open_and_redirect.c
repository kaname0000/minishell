/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:42:22 by yookamot          #+#    #+#             */
/*   Updated: 2024/12/11 16:48:47 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_and_redirect_in(char *infile)
{
	int	fd_in;

	if (access(infile, F_OK) == -1 || access(infile, R_OK) == -1)
	{
		error_infile_invalid(infile);
		return (-1);
	}
	fd_in = open(infile, O_RDONLY);
	if (fd_in == -1)
	{
		error_infile_open_failed(infile);
		return (-1);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
		error_redirect();
	if (close(fd_in) == -1)
	{
		error_infile_close_failed();
		return (-1);
	}
	return (0);
}

void	open_and_redirect_out(pid_t pid1, char *outfile)
{
	int	fd_out;

	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
		error_outfile_invalid(pid1, outfile);
	fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		error_outfile_open_failed(pid1, outfile);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		error_redirect_out(pid1);
	if (close(fd_out) == -1)
		error_outfile_close_failed(pid1);
}
