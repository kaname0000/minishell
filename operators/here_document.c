/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:24:05 by okaname           #+#    #+#             */
/*   Updated: 2025/05/25 18:20:43 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "operators.h"

static void	free_close_exit(char *line, int fd, int status)
{
	free(line);
	close(fd);
	exit(status);
}

static void	wated_eof(t_mini *mini, char *eof, int fd)
{
	ft_putstr_fd("bash: warning: here-document at line ", 2);
	ft_putnbr_fd(mini->line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(eof, 2);
	ft_putstr_fd("')\n", 2);
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
		error_fork(mini, tokenset);
	else if (pid == 0)
	{
		set_sig_heredoc();
		line = NULL;
		while (1)
		{
			line = readline("> ");
			if (!line)
				wated_eof(mini, char_EOF, pipefd);
			if (!ft_strcmp(line, char_EOF))
				free_close_exit(line, pipefd, 0);
			if (mini->expand_flag)
				line = expand_line(line, mini);
			write(pipefd, line, ft_strlen(line));
			write(pipefd, "\n", 1);
			free(line);
		}
	}
	return (pid);
}

int	here_doc(char *char_EOF, int *fd, t_mini *mini, t_tokenset *tokenset)
{
	int	pipefd[2];
	int	wstatus;
	int	pid;

	if (*fd != 0)
		close(*fd);
	if (pipe(pipefd) < 0)
	{
		free_mini(mini);
		free_tokenset(tokenset, SUCCESS);
		error_pipe();
	}
	pid = get_doc(pipefd[1], char_EOF, mini, tokenset);
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		mini->exit_status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		mini->exit_status = 128 + WTERMSIG(wstatus);
	close(pipefd[1]);
	*fd = pipefd[0];
	return (0);
}
