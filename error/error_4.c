/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:17:51 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/12 20:31:24 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	error_fork2(pid_t pid1)
{
	perror("minishell: fork");
	if (pid1 != -1)
		waitpid(pid1, NULL, 0);
	exit(1);
}

void	error_redirect_out(pid_t pid1)
{
	perror("minishell");
	if (pid1 != -1)
		waitpid(pid1, NULL, 0);
	exit(1);
}

void	error_command1_directory(char *cmd_parts)
{
	ft_putstr_fd("minishell: ", 2);
	perror(cmd_parts);
	free(cmd_parts);
	exit(126);
}

void	error_command2_directory(pid_t pid1, char **cmd_parts)
{
	ft_putstr_fd("minishell: ", 2);
	perror(cmd_parts[0]);
	ft_free_split(cmd_parts);
	if (pid1 != -1)
		waitpid(pid1, NULL, 0);
	exit(126);
}

void	error_command1_nonexistent(char *cmd_parts)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_parts, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free(cmd_parts);
	exit(127);
}
