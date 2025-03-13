/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:03:51 by okaname           #+#    #+#             */
/*   Updated: 2025/03/13 20:12:36 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operators.h"

int	pipex(int *fd_in, int *fd_out)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
		error_pipe();
	if (*fd_out != 0 && close(pipefd[1]) == -1)
		error_outfile_close_failed();
	else
		*fd_out = pipefd[1];
	*fd_in = pipefd[0];
}
