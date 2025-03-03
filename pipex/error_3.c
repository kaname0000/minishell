/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:51:14 by yookamot          #+#    #+#             */
/*   Updated: 2024/12/17 19:05:37 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_outfile_invalid(pid_t pid1, char *outfile)
{
	write(2, "bash: ", ft_strlen("bash: "));
	perror(outfile);
	if (pid1 != -1)
		waitpid(pid1, NULL, 0);
	exit(1);
}

void	error_outfile_open_failed(pid_t pid1, char *outfile)
{
	write(2, "bash: ", ft_strlen("bash: "));
	perror(outfile);
	if (pid1 != -1)
		waitpid(pid1, NULL, 0);
	exit(1);
}

void	error_outfile_close_failed(pid_t pid1)
{
	perror("bash: close");
	if (pid1 != -1)
		waitpid(pid1, NULL, 0);
	exit(1);
}

void	error_command2(pid_t pid1, char **cmd_parts)
{
	write(2, cmd_parts[0], ft_strlen(cmd_parts[0]));
	write(2, ": command not found\n", 21);
	ft_free_split(cmd_parts);
	if (pid1 != -1)
		waitpid(pid1, NULL, 0);
	exit(127);
}

void	error_execve2(pid_t pid1, char *full_path, char **cmd_args)
{
	free(full_path);
	ft_free_split(cmd_args);
	cmd_args = NULL;
	perror("bash");
	if (pid1 != -1)
		waitpid(pid1, NULL, 0);
	if (errno == ENOENT)
		exit(127);
	if (errno == EACCES || errno == ELIBBAD)
		exit(126);
	else
		exit(1);
}
