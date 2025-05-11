/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:17:08 by okaname           #+#    #+#             */
/*   Updated: 2025/05/11 21:56:55 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "operators.h"

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
