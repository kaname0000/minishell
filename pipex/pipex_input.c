/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:16:37 by yookamot          #+#    #+#             */
/*   Updated: 2024/12/11 20:37:02 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	pipex_input(char **argv, char **envp, int *pipefd)
{
	char	*cmd1_path;
	pid_t	pid1;

	if (open_and_redirect_in(argv[1]) == -1)
		return (-1);
	cmd1_path = get_full_path1(argv[2], envp);
	if (!cmd1_path)
		return (-1);
	pid1 = return_pid1(argv, cmd1_path, envp, pipefd);
	return (pid1);
}
