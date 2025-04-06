/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:10:01 by okaname           #+#    #+#             */
/*   Updated: 2025/04/06 21:42:43 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_built_in(t_mini *mini, t_token **token)
{
	int	stdin;
	int	stdout;

	if (set_fd_b(mini->cmd[0], token) == 1)
	{
		mini->exit_status = 1;
		return (0);
	}
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	if (dup2(mini->cmd[0]->fd_in, STDIN_FILENO) == -1)
		error_redirect();
	if (mini->cmd[0]->fd_in != STDIN_FILENO && close(mini->cmd[0]->fd_in) == -1)
		error_close();
	if (dup2(mini->cmd[0]->fd_out, STDOUT_FILENO) == -1)
		error_redirect();
	if (mini->cmd[0]->fd_out != 1 && close(mini->cmd[0]->fd_out) == -1)
		error_close();
	printf("built in commandを実行するよ\n");
	dup2(stdout, STDOUT_FILENO);
	close(stdout);
	dup2(stdin, STDIN_FILENO);
	close(stdin);
	printf("built in commandだよ\n");
	return (0);
}
