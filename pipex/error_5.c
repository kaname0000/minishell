/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:09:59 by yookamot          #+#    #+#             */
/*   Updated: 2024/12/14 18:23:39 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_command2_nonexistent(pid_t pid1, char **cmd_parts)
{
	write(2, "bash: ", 6);
	write(2, cmd_parts[0], ft_strlen(cmd_parts[0]));
	write(2, ": No such file or directory\n",
		ft_strlen(": No such file or directory\n"));
	ft_free_split(cmd_parts);
	if (pid1 != -1)
		waitpid(pid1, NULL, 0);
	exit(127);
}
