/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:03:51 by okaname           #+#    #+#             */
/*   Updated: 2025/04/16 21:24:59 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	pipex(int *fd_in, int *fd_out, t_mini *mini, t_tokenset *tokenset)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
	{
		free_mini(mini);
		free_tokenset1(tokenset);
		error_pipe();
	}
	if (*fd_out != 1)
		close(*fd_out);
	*fd_out = pipefd[1];
	if (*fd_in != 0)
		close(*fd_in);
	*fd_in = pipefd[0];
	return (0);
}

void	conect_pipe(t_command **cmd, t_mini *mini, t_tokenset *tokenset)
{
	int	i;

	i = 0;
	while (cmd[i + 1] != NULL)
	{
		pipex(&(cmd[i + 1]->fd_in), &(cmd[i]->fd_out), mini, tokenset);
		i++;
	}
}
