/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:37:12 by okaname           #+#    #+#             */
/*   Updated: 2025/04/05 02:30:51 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operators.h"

pid_t	redirector(t_command *cmd)
{
	printf("aa\n");
	cmd->cmd_path = get_full_path(cmd->cmd[0], cmd->envp);
	printf("%s\n", cmd->cmd_path);
	if (cmd->cmd_path == NULL)
		return (-1);
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		error_redirect();
	if (cmd->fd_in != STDIN_FILENO && close(cmd->fd_in) == -1)
		error_close();
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		error_redirect();
	if (cmd->fd_out != STDOUT_FILENO && close(cmd->fd_out) == -1)
		error_close();
	execve(cmd->cmd_path, cmd->cmd, cmd->envp);
	perror("bash");
	return (0);
}

// pid_t	redirector(t_mini *minishell)
// {
// 	pid_t	pid;

// 	cmd->cmd_path = get_full_path(cmd->cmd[0], cmd->envp);
// 	if (cmd->cmd_path == NULL)
// 		return (-1);
// 	pid = fork();
// 	if (pid == -1)
// 		return (free(cmd->cmd_path), error_fork1(), -1);
// 	else if (pid == 0)
// 	{
// 		if (execve_child_process(cmd) == -1)
// 			return (free(cmd->cmd_path), -1);
// 	}
// 	if (waitpid(pid, status, 0) == -1)
// 	{
// 		perror("waitpid");
// 		return (free(cmd->cmd_path), 1);
// 	}
// 	if (WIFEXITED(*status))
// 		printf("Child exited with status %d\n", WEXITSTATUS(*status));
// 	return (free(cmd->cmd_path), pid);
// }
