/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:45:19 by yookamot          #+#    #+#             */
/*   Updated: 2024/12/08 20:17:57 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	pipex_output(pid_t pid1, char **argv, char **envp, int *pipefd)
{
	pid_t	pid2;

	open_and_redirect_out(pid1, argv[4]);
	pid2 = return_pid2(pid1, argv, envp, pipefd);
	return (pid2);
}
