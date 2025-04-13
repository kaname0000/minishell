/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_prosses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:49:58 by okaname           #+#    #+#             */
/*   Updated: 2025/04/13 18:29:27 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_in_command/built_in.h"
#include "../error/error.h"
#include "../minishell.h"
#include "operators.h"

int	make_prosses(t_mini *mini, t_tokenset *tokenlist, int count, int **pid)
{
	(*pid)[count] = fork();
	if ((*pid)[count] == -1)
		return (error_fork(mini, tokenlist, *pid), -1);
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
	return (0);
}
