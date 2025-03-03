/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_pid2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:12:07 by yookamot          #+#    #+#             */
/*   Updated: 2024/12/11 22:05:09 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	execve_child_process2(pid_t pid1, char **argv, char **envp,
		int *pipefd)
{
	char	*full_path;
	char	**cmd2_args;

	cmd2_args = ft_split(argv[3], ' ');
	if (!cmd2_args)
		error_malloc(NULL, NULL);
	if (close(pipefd[1]) == -1)
	{
		ft_free_split(cmd2_args);
		error_outfile_close_failed(pid1);
	}
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		ft_free_split(cmd2_args);
		error_redirect();
	}
	if (close(pipefd[0]) == -1)
	{
		ft_free_split(cmd2_args);
		error_outfile_close_failed(pid1);
	}
	full_path = get_full_path2(pid1, argv[3], envp);
	execve(full_path, cmd2_args, envp);
	error_execve2(pid1, full_path, cmd2_args);
	return (-1);
}

static pid_t	fork_child_process2(pid_t pid1, char **argv, char **envp,
		int *pipefd)
{
	pid_t	pid2;
	int		i;

	i = 0;
	pid2 = fork();
	if (pid2 == -1)
		return (-1);
	if (pid2 == 0)
	{
		if (execve_child_process2(pid1, argv, envp, pipefd) == -1)
			return (-1);
	}
	return (pid2);
}

pid_t	return_pid2(pid_t pid1, char **argv, char **envp, int *pipefd)
{
	pid_t	pid2;

	pid2 = fork_child_process2(pid1, argv, envp, pipefd);
	if (pid2 == -1)
		error_fork2(pid1);
	return (pid2);
}
