/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:37:12 by okaname           #+#    #+#             */
/*   Updated: 2025/03/10 18:04:55 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operators.h"

static int	execve_child_process(t_command *cmd)
{
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		return (-1);
	if (cmd->fd_in != STDIN_FILENO && close(cmd->fd_in) == -1)
		return (-1);
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		return (-1);
	if (cmd->fd_out != STDOUT_FILENO && close(cmd->fd_out) == -1)
		return (-1);
	execve(cmd->cmd_path, cmd->cmd, cmd->envp);
	return (-1);
}

// static int	open_infile(char *infile)
// {
// 	int	fd_in;

// 	if (access(infile, F_OK) == -1 || access(infile, R_OK) == -1)
// 		return (-1);
// 	fd_in = open(infile, O_RDONLY);
// 	if (fd_in == -1)
// 		return (-1);
// 	return (fd_in);
// }

static int	open_outfile(char *outfile)
{
	int	fd_out;

	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
		return (-1);
	fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		return (-1);
	return (fd_out);
}

pid_t	redirector(t_command *cmd)
{
	pid_t	pid;

	cmd->cmd_path = get_full_path(cmd->cmd[0], cmd->envp);
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		if (execve_child_process(cmd) == -1)
			return (-1);
	}
	wait(NULL);
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	t_command	cmd;

	(void)argc;
	cmd.cmd = ft_split(argv[1], ' ');
	cmd.envp = envp;
	cmd.fd_out = open_outfile(argv[3]);
	here_doc(&cmd, argv[2]);
	return (0);
}
