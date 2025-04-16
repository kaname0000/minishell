/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:24:05 by okaname           #+#    #+#             */
/*   Updated: 2025/04/16 21:53:47 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operators.h"

extern t_signal	g_variable;

static void	free_close_exit(char *line, int fd)
{
	free(line);
	close(fd);
	exit(0);
}

static int	get_doc(int pipefd, char *char_EOF, t_mini *mini,
		t_tokenset *tokenset)
{
	char	*line;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_fork(mini, tokenset, NULL);
	else if (pid == 0)
	{
		g_variable.input_mode = HERE_DOC;
		line = NULL;
		while (1)
		{
			line = readline("> ");
			if (line == NULL)
				free_close_exit(line, pipefd);
			if (!ft_strcmp(line, char_EOF))
				free_close_exit(line, pipefd);
			write(pipefd, line, ft_strlen(line));
			write(pipefd, "\n", 1);
			free(line);
		}
	}
	waitpid(pid, &mini->exit_status, 0);
	return (0);
}

int	here_doc(char *char_EOF, int *fd, t_mini *mini, t_tokenset *tokenset)
{
	int	pipefd[2];

	if (*fd != 0)
		close(*fd);
	if (pipe(pipefd) < 0)
	{
		free_mini(mini);
		free_tokenset1(tokenset);
		error_pipe();
	}
	get_doc(pipefd[1], char_EOF, mini, tokenset);
	close(pipefd[1]);
	*fd = pipefd[0];
	return (0);
}
