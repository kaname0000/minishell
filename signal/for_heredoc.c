/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:03:03 by okaname           #+#    #+#             */
/*   Updated: 2025/05/11 21:46:07 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <readline/readline.h>
#include <stdio.h>

static void	sigint_handler_for_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(130);
	}
}

void	set_sig_heredoc(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_handler_for_heredoc;
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&(sa_int.sa_mask));
	sigemptyset(&(sa_quit.sa_mask));
	sa_int.sa_flags = 0;
	sa_quit.sa_flags = 0;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		perror("sigaction SIGINT");
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		perror("sigaction SIGQUIT");
}
