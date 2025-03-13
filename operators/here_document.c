/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:24:05 by okaname           #+#    #+#             */
/*   Updated: 2025/03/13 18:06:58 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operators.h"

void	malloc_error(void)
{
	printf("malloc error");
	exit(1);
}

static int	get_doc(int pipefd, char *char_EOF)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			malloc_error();
		if (!ft_strncmp(line, char_EOF, ft_strlen(char_EOF)))
			return (free(line), 0);
		write(pipefd, line, ft_strlen(line));
		write(pipefd, "\n", 1);
		free(line);
	}
}

int	here_doc(char *char_EOF)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
		error_pipe();
	get_doc(pipefd[1], char_EOF);
	close(pipefd[1]);
	return (pipefd[0]);
}
