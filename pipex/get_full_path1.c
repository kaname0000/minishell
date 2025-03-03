/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_path1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:57:27 by yookamot          #+#    #+#             */
/*   Updated: 2024/12/14 18:22:05 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*check_file_or_directory(char **cmd_parts)
{
	int		fd;
	char	*full_path;
	char	*buffer;

	buffer = NULL;
	if (access(cmd_parts[0], F_OK) != 0)
		return (error_command1_nonexistent(cmd_parts), NULL);
	fd = open(cmd_parts[0], O_RDONLY);
	read(fd, buffer, sizeof(buffer));
	if (errno == EISDIR)
		return (error_command1_directory(cmd_parts), close(fd), NULL);
	close(fd);
	if (access(cmd_parts[0], X_OK) != 0)
		return (error_command1(cmd_parts), NULL);
	full_path = ft_strdup(cmd_parts[0]);
	if (!full_path)
		error_malloc(cmd_parts, NULL);
	return (ft_free_split(cmd_parts), full_path);
}

static char	*search_envp_path(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (path);
}

static char	*find_executable_path1(char **cmd_parts, char **path_parts)
{
	int		i;
	char	*full_path;
	char	*temp;

	i = 0;
	while (path_parts[i])
	{
		temp = ft_strjoin(path_parts[i], "/");
		if (!temp)
			error_malloc(cmd_parts, path_parts);
		full_path = ft_strjoin_free(temp, cmd_parts[0]);
		if (!full_path)
			error_malloc(cmd_parts, path_parts);
		if (access(full_path, X_OK) == 0)
			return (ft_free_split(cmd_parts), ft_free_split(path_parts),
				full_path);
		free(full_path);
		full_path = NULL;
		i++;
	}
	ft_free_split(path_parts);
	error_command1(cmd_parts);
	return (NULL);
}

char	*get_full_path1(char *cmd, char **envp)
{
	char	**cmd_parts;
	char	*full_path;
	char	*path;
	char	**path_parts;

	cmd_parts = ft_split(cmd, ' ');
	if (!cmd_parts)
		error_malloc(NULL, NULL);
	if (ft_strchr(cmd_parts[0], '/'))
	{
		full_path = check_file_or_directory(cmd_parts);
		return (full_path);
	}
	path = search_envp_path(envp);
	if (!path)
		return (error_command1(cmd_parts), NULL);
	path_parts = ft_split(path, ':');
	if (!path_parts)
		error_malloc(cmd_parts, NULL);
	full_path = find_executable_path1(cmd_parts, path_parts);
	return (full_path);
}
