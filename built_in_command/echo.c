/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:46:28 by okaname           #+#    #+#             */
/*   Updated: 2025/05/12 18:09:36 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	ft_echo(t_mini *mini, int count)
{
	int		i;
	bool	nflag;

	i = 1;
	nflag = false;
	while (mini->cmd[count]->cmd[i] != NULL)
	{
		if (!ft_strcmp(mini->cmd[count]->cmd[i], "-n"))
			nflag = true;
		else
			printf("%s", mini->cmd[count]->cmd[i]);
		i++;
		if (mini->cmd[count]->cmd[i] == NULL)
			break ;
		printf(" ");
	}
	if (!nflag)
		printf("\n");
	return (0);
}
