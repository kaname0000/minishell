/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:17:51 by yookamot          #+#    #+#             */
/*   Updated: 2024/12/14 18:24:29 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_fork2(pid_t pid1)
{
	perror("bash: fork");
	if (pid1 != -1)
		waitpid(pid1, NULL, 0);
	exit(1);
}

void	error_redirect_out(pid_t pid1)
{
	perror("bash");
	if (pid1 != -1)
		waitpid(pid1, NULL, 0);
	exit(1);
}

void	error_command1_directory(char **cmd_parts)
{
	write(2, "bash: ", 6);
	perror(cmd_parts[0]);
	ft_free_split(cmd_parts);
}

void	error_command2_directory(pid_t pid1, char **cmd_parts)
{
	write(2, "bash: ", 6);
	perror(cmd_parts[0]);
	ft_free_split(cmd_parts);
	if (pid1 != -1)
		waitpid(pid1, NULL, 0);
	exit(126);
}

void	error_command1_nonexistent(char **cmd_parts)
{
	write(2, "bash: ", 6);
	write(2, cmd_parts[0], ft_strlen(cmd_parts[0]));
	write(2, ": No such file or directory\n",
		ft_strlen(": No such file or directory\n"));
	ft_free_split(cmd_parts);
}
