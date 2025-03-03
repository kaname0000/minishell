/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:22:23 by yookamot          #+#    #+#             */
/*   Updated: 2024/12/11 20:51:35 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_process(int *pipefd, pid_t pid1, pid_t pid2)
{
	int	status;
	int	exit_code;

	if (close(pipefd[0]) == -1)
		error_outfile_close_failed(pid1);
	if (close(pipefd[1]) == -1)
		error_outfile_close_failed(pid1);
	if (pid1 != -1)
		waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		exit(exit_code);
	}
}
