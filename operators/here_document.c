/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:24:05 by okaname           #+#    #+#             */
/*   Updated: 2025/04/06 19:17:03 by okaname          ###   ########.fr       */
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

static void	exit_doc(char *char_EOF, int line)
{
	char	*c_line;

	c_line = ft_itoa(line);
	if (c_line == NULL)
		error_malloc(NULL, NULL);
	ft_putstr_fd("bash: warning: here-document at line ", 2);
	ft_putstr_fd(c_line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(char_EOF, 2);
	ft_putstr_fd("`)\n", 2);
	free(c_line);
	exit(0);
}

static int	max_len(char *s1, char *s2)
{
	int	i;
	int	j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (i > j)
		return (i);
	else
		return (j);
}

static int	get_doc(int pipefd, char *char_EOF, int *status)
{
	char	*line;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_fork1();
	else if (pid == 0)
	{
		g_variable.input_mode = HERE_DOC;
		line = NULL;
		while (1)
		{
			line = readline("> ");
			if (line == NULL)
				exit_doc(char_EOF, 1);
			if (!ft_strncmp(line, char_EOF, max_len(line, char_EOF)))
				free_close_exit(line, pipefd);
			write(pipefd, line, ft_strlen(line));
			write(pipefd, "\n", 1);
			free(line);
		}
	}
	waitpid(pid, status, 0);
	return (0);
}

int	here_doc(char *char_EOF, int *fd, int *status)
{
	int	pipefd[2];

	if (*fd != 0 && close(*fd) == -1)
		return (-1);
	if (pipe(pipefd) < 0)
		error_pipe();
	get_doc(pipefd[1], char_EOF, status);
	if (close(pipefd[1]) == -1)
		return (-1);
	*fd = pipefd[0];
	return (0);
}
