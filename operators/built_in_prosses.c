/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_prosses.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:14:56 by okaname           #+#    #+#             */
/*   Updated: 2025/04/16 21:36:57 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	built_in_prosses(t_mini *mini, int count)
{
	if (dup2(mini->cmd[count]->fd_in, STDIN_FILENO) == -1)
		error_redirect();
	if (mini->cmd[count]->fd_in != STDIN_FILENO)
		close(mini->cmd[count]->fd_in);
	if (dup2(mini->cmd[count]->fd_out, STDOUT_FILENO) == -1)
		error_redirect();
	if (mini->cmd[count]->fd_out != STDOUT_FILENO)
		close(mini->cmd[count]->fd_out);
	if (run_cmd(mini, count) != 0)
		exit(1);
	exit(0);
}
