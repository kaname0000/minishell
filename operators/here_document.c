/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:24:05 by okaname           #+#    #+#             */
/*   Updated: 2025/03/26 16:42:24 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operators.h"

extern t_signal	g_variable;

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

static int	get_doc(int pipefd, char *char_EOF)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			exit_doc(char_EOF, 1);
		if (!ft_strncmp(line, char_EOF, ft_strlen(char_EOF)))
			return (free(line), 0);
		write(pipefd, line, ft_strlen(line));
		write(pipefd, "\n", 1);
		free(line);
	}
}

int	here_doc(char *char_EOF, int *last, int *fd)
{
	int	pipefd[2];

	*last = HERE_DOC;
	g_variable.input_mode = HERE_DOC;
	if (*fd != 0 && close(*fd) == -1)
		return (-1);
	if (pipe(pipefd) < 0)
		error_pipe();
	get_doc(pipefd[1], char_EOF);
	if (close(pipefd[1]) == -1)
		return (-1);
	*fd = pipefd[0];
	return (0);
}
