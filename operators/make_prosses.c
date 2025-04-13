/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_prosses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:49:58 by okaname           #+#    #+#             */
/*   Updated: 2025/04/13 16:47:09 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_cmd(t_command *cmd)
{
	free_array(cmd->cmd);
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
		if (mini->cmd[count]->built_in)
			built_in_prosses(mini, count);
		else
			redirector(mini->cmd[count]);
	}
	if (mini->cmd[count]->fd_in != STDIN_FILENO
		&& close(mini->cmd[count]->fd_in) == -1)
		error_close();
	if (mini->cmd[count]->fd_out != STDOUT_FILENO
		&& close(mini->cmd[count]->fd_out) == -1)
		error_close();
	free_cmd(mini->cmd[count]);
	return (0);
}
