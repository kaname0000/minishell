/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_prosses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 01:25:14 by okaname           #+#    #+#             */
/*   Updated: 2025/04/06 17:42:19 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cmd(t_command **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		free_array(cmd[i]->cmd);
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

int	make_prosses(t_mini *mini, t_tokenset *tokenlist, int count, int **pid)
{
	(*pid)[count] = fork();
	if ((*pid)[count] == -1)
		return (error_fork1(), -1);
	else if ((*pid)[count] == 0)
	{
		set_fd(&(mini->cmd[count]), tokenlist->token, count);
		mini->cmd[count]->envp = list_to_char(mini->var_env);
		redirector(mini->cmd[count]);
	}
	if (mini->cmd[count]->fd_in != STDIN_FILENO
		&& close(mini->cmd[count]->fd_in) == -1)
		error_close();
	if (mini->cmd[count]->fd_out != STDOUT_FILENO
		&& close(mini->cmd[count]->fd_out) == -1)
		error_close();
	free_cmd(mini->cmd);
	wait(&(*pid)[count]);
	return (0);
}
