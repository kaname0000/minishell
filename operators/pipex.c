/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:03:51 by okaname           #+#    #+#             */
/*   Updated: 2025/04/13 16:47:19 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipex(int *fd_in, int *fd_out)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
		error_pipe();
	if (*fd_out != 1)
	{
		if (close(*fd_out) == -1)
			error_close();
	}
	*fd_out = pipefd[1];
	if (*fd_in != 0)
	{
		if (close(*fd_in) == -1)
			error_close();
	}
	*fd_in = pipefd[0];
	return (0);
}

void	conect_pipe(t_command **cmd)
{
	int	i;

	i = 0;
	while (cmd[i + 1] != NULL)
	{
		pipex(&(cmd[i + 1]->fd_in), &(cmd[i]->fd_out));
		i++;
	}
}
