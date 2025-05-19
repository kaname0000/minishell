/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:51:14 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/19 21:01:19 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	error_outfile_invalid(pid_t pid1, char *outfile)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	perror(outfile);
	if (pid1 != -1)
		waitpid(pid1, NULL, 0);
	exit(1);
}

void	error_outfile_open_failed(pid_t pid1, char *outfile)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	perror(outfile);
	if (pid1 != -1)
		waitpid(pid1, NULL, 0);
	exit(1);
}

void	error_outfile_close_failed(pid_t pid1)
{
	perror("minishell: close");
	if (pid1 != -1)
		waitpid(pid1, NULL, 0);
	exit(1);
}

void	error_command2(char *cmd_parts)
{
	write(2, cmd_parts, ft_strlen(cmd_parts));
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	error_execve2(pid_t pid1, char *full_path, char **cmd_args)
{
	free(full_path);
	ft_free_split(cmd_args);
	cmd_args = NULL;
	perror("minishell");
	if (pid1 != -1)
		waitpid(pid1, NULL, 0);
	if (errno == ENOENT)
		exit(127);
	if (errno == EACCES || errno == ELIBBAD)
		exit(126);
	else
		exit(1);
}
