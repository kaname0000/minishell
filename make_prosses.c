/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_prosses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 01:25:14 by okaname           #+#    #+#             */
/*   Updated: 2025/04/05 02:24:24 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_prosses(t_mini *mini, t_tokenset *tokenlist, int count, int **pid)
{
	(*pid)[count] = fork();
	if ((*pid)[count] == -1)
		return (error_fork1(), -1);
	else if ((*pid)[count] == 0)
	{
		set_fd(&(mini->cmd[count]), tokenlist->token, count);
		mini->cmd[count]->envp = list_to_char(mini->var_env);
		redirector(mini->cmd[count]);
	}
	wait(&(*pid)[count]);
	return (0);
}
