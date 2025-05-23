/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:33:13 by okaname           #+#    #+#             */
/*   Updated: 2025/05/23 23:55:14 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operators.h"

static char	*check_file_or_directory(char *cmd, char *display_cmd)
{
	int		fd;
	char	*full_path;
	char	buffer[1];

	if (access(cmd, F_OK) != 0)
		return (error_command1_nonexistent(display_cmd), NULL);
	fd = open(cmd, O_RDONLY);
	if (read(fd, buffer, 1) < 0 && errno == EISDIR)
		return (error_command1_directory(display_cmd), close(fd), NULL);
	close(fd);
	if (access(cmd, X_OK) != 0)
		return (error_command1(display_cmd), NULL);
	full_path = ft_strdup(cmd);
	if (!full_path)
		error_malloc(NULL, NULL);
	return (ft_free_split(NULL), full_path);
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

static char	*find_executable_path1(char *cmd, char **path_parts)
{
	int		i;
	char	*full_path;
	char	*temp;

	i = 0;
	while (path_parts[i])
	{
		temp = ft_strjoin(path_parts[i], "/");
		if (!temp)
			error_malloc(NULL, path_parts);
		full_path = ft_strjoin_free(temp, cmd);
		if (!full_path)
			error_malloc(NULL, path_parts);
		if (access(full_path, X_OK) == 0)
			return (ft_free_split(path_parts), full_path);
		free(full_path);
		full_path = NULL;
		i++;
	}
	ft_free_split(path_parts);
	error_command1(cmd);
	return (NULL);
}

char	*get_full_path(char *cmd, char **envp)
{
	char	*full_path;
	char	*path;
	char	**path_parts;
	char	*dot_slash_cmd;

	if (ft_strchr(cmd, '/'))
		return (check_file_or_directory(cmd, cmd));
	path = search_envp_path(envp);
	if (!path)
	{
		dot_slash_cmd = ft_strjoin("./", cmd);
		if (!dot_slash_cmd)
			error_malloc(NULL, NULL);
		full_path = check_file_or_directory(dot_slash_cmd, cmd);
		free(dot_slash_cmd);
		return (full_path);
	}
	path_parts = ft_split(path, ':');
	if (!path_parts)
		error_malloc(NULL, NULL);
	full_path = find_executable_path1(cmd, path_parts);
	return (full_path);
}
