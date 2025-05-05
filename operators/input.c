/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:17:08 by okaname           #+#    #+#             */
/*   Updated: 2025/05/05 21:53:43 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "operators.h"

extern t_signal	g_variable;

int	input(t_mini *minishell)
{
	while (1)
	{
		set_sig_prompt();
		minishell->input = readline("minishell$ ");
		if (minishell->input == NULL)
		{
			free(minishell->input);
			break ;
		}
		if (*minishell->input == '\0')
		{
			free(minishell->input);
			continue ;
		}
		add_history(minishell->input);
		run_token(minishell);
	}
	printf("exit\n");
	return (0);
}
