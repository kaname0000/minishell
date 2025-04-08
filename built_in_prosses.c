/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_prosses.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:14:56 by okaname           #+#    #+#             */
/*   Updated: 2025/04/08 21:56:19 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in_prosses(t_mini *mini, int count)
{
	if (dup2(mini->cmd[count]->fd_in, STDIN_FILENO) == -1)
		error_redirect();
	if (mini->cmd[count]->fd_in != STDIN_FILENO
		&& close(mini->cmd[count]->fd_in) == -1)
		error_close();
	if (dup2(mini->cmd[count]->fd_out, STDOUT_FILENO) == -1)
		error_redirect();
	if (mini->cmd[count]->fd_out != STDOUT_FILENO
		&& close(mini->cmd[count]->fd_out) == -1)
		error_close();
	if (run_cmd(mini, count) != 0)
		exit(1);
	exit(0);
	return (0);
}
