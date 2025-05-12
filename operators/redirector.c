/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:37:12 by okaname           #+#    #+#             */
/*   Updated: 2025/05/12 18:26:13 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operators.h"

void	redirector(t_command *cmd)
{
	cmd->cmd_path = get_full_path(cmd->cmd[0], cmd->envp);
	if (cmd->cmd_path == NULL)
		exit(1);
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		error_redirect();
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		error_redirect();
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	execve(cmd->cmd_path, cmd->cmd, cmd->envp);
	perror("minishell");
	exit(1);
}
