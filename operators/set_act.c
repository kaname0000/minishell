/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_act.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:53:45 by okaname           #+#    #+#             */
/*   Updated: 2025/05/04 22:37:22 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "operators.h"

extern t_signal	g_variable;

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig != SIGINT)
		return ;
	if (g_variable.mode == COMMAND_LINE)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_variable.mode == C_HERE_DOC)
	{
		printf("呼ばれたよ\n");
		g_variable.heredoc_int = 1;
		exit(130);
	}
}

void	set_act(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit(1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(1);
}
