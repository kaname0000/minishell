/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:09:45 by okaname           #+#    #+#             */
/*   Updated: 2025/03/04 20:50:49 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static char	*get_full_path(char *dir, char *command)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(dir, "/");
	if (tmp == NULL)
		return (free(tmp), NULL);
	result = ft_strjoin(tmp, command);
	free(tmp);
	if (result == NULL)
		return (NULL);
	return (result);
}

static char	*find_executable(char *command)
{
	char		*path;
	char		*path_copy;
	char		*dir;
	static char	*full_path;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	path_copy = ft_strdup(path);
	if (!path_copy)
		return (NULL);
	dir = ft_strtok(path_copy, ":");
	while (dir)
	{
		full_path = get_full_path(dir, command);
		if (full_path == NULL || access(full_path, X_OK) == 0)
			return (free(path_copy), full_path);
		dir = ft_strtok(NULL, ":");
	}
	return (free(path_copy), NULL);
}

int	excute(char **command, char **envp)
{
	pid_t	pid;
	char	*full_path;
	int		status;

	full_path = find_executable(command[0]);
	if (!full_path)
	{
		fprintf(stderr, "Command not found: %s\n", command[0]);
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		if (access(full_path, X_OK) == -1)
		{
			perror("access");
			exit(1);
		}
		execve(full_path, command, envp);
		perror("execve");
		exit(1);
	}
	else
	{
		if (wait(&status) == -1)
		{
			perror("wait");
			return (1);
		}
	}
	return (0);
}
