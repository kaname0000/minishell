/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:06:24 by okaname           #+#    #+#             */
/*   Updated: 2025/04/13 17:43:14 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	free_cmd(t_command **cmd)
{
	int	i;

	if (cmd == NULL)
		return ;
	i = 0;
	while (cmd[i] != NULL)
	{
		free_array(cmd[i]->cmd);
		free(cmd);
		i++;
	}
}
