/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:06:21 by okaname           #+#    #+#             */
/*   Updated: 2025/03/25 22:31:33 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_openfile(char *file)
{
	ft_putstr_fd("bash: ", 2);
	perror(file);
}

int	open_infile(char *infile)
{
	int	fd_in;

	if (access(infile, F_OK) == -1 || access(infile, R_OK) == -1)
		return (error_openfile(infile), -1);
	fd_in = open(infile, O_RDONLY);
	if (fd_in == -1)
		return (error_openfile(infile), -1);
	return (fd_in);
}

int	open_outfile(char *outfile)
{
	int	fd_out;

	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
		return (error_openfile(outfile), -1);
	fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		return (error_openfile(outfile), -1);
	return (fd_out);
}

int	open_appendfile(char *appendfile)
{
	int	fd_out;

	if (access(appendfile, F_OK) == 0 && access(appendfile, W_OK) == -1)
		return (error_openfile(appendfile), -1);
	fd_out = open(appendfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd_out == -1)
		return (error_openfile(appendfile), -1);
	return (fd_out);
}
