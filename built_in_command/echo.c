/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:46:28 by okaname           #+#    #+#             */
/*   Updated: 2025/05/25 17:50:08 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	is_all_n(char *n)
{
	int	i;

	i = 0;
	while (n[i] != '\0')
	{
		if (n[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_mini *mini, int count)
{
	int		i;
	bool	nflag;

	i = 1;
	nflag = false;
	if (!ft_strncmp(mini->cmd[count]->cmd[i], "-n", 2)
		&& is_all_n(&(mini->cmd[count]->cmd[i][2])))
	{
		i++;
		nflag = true;
	}
	while (mini->cmd[count]->cmd[i] != NULL)
	{
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
