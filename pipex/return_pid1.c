/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_pid1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:25:07 by yookamot          #+#    #+#             */
/*   Updated: 2024/12/11 17:57:05 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	execve_child_process1(char **cmd1_args, char *full_path,
		char **envp, int *pipefd)
{
	if (close(pipefd[0]) == -1)
	{
		error_infile_close_failed();
		return (-1);
	}
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		error_redirect();
	if (close(pipefd[1]) == -1)
	{
		error_infile_close_failed();
		return (-1);
	}
	execve(full_path, cmd1_args, envp);
	error_execve1();
	return (-1);
}

static pid_t	fork_child_process1(char **argv, char *full_path, char **envp,
		int *pipefd)
{
	pid_t	pid1;
	char	**cmd1_args;
	int		i;

	i = 0;
	cmd1_args = ft_split(argv[2], ' ');
	if (!cmd1_args)
	{
		free(full_path);
		error_malloc(NULL, NULL);
	}
	pid1 = fork();
	if (pid1 == -1)
		return (ft_free_split(cmd1_args), free(full_path), -1);
	if (pid1 == 0)
	{
		if (execve_child_process1(cmd1_args, full_path, envp, pipefd) == -1)
			return (ft_free_split(cmd1_args), free(full_path), -1);
	}
	return (ft_free_split(cmd1_args), free(full_path), pid1);
}

pid_t	return_pid1(char **argv, char *full_path, char **envp, int *pipefd)
{
	pid_t	pid1;

	pid1 = fork_child_process1(argv, full_path, envp, pipefd);
	if (pid1 == -1)
		error_fork1();
	return (pid1);
}
