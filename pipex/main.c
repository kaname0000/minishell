/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:33:49 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/03 15:47:42 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	int		i;
	pid_t	pid1;
	pid_t	pid2;

	i = 1;
	if (argc != 5)
		error_arg();
	while (i < 5)
	{
		if (argv[i][0] == '\0')
			error_arg();
		i++;
	}
	if (pipe(pipefd) == -1)
		error_pipe();
	pid1 = pipex_input(argv, envp, pipefd);
	pid2 = pipex_output(pid1, argv, envp, pipefd);
	close_process(pipefd, pid1, pid2);
	return (0);
}
