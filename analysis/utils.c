/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:26:45 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/04 17:59:09 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"

void	free_array(void **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return ;
}

void	free_values(t_tokenlist *tokenlist, int i, int j)
{
	int	x;
	int	y;

	x = 0;
	while (x < i)
	{
		y = 0;
		while (y < tokenlist->size[x])
		{
			free(tokenlist->token[x][y].value);
			y++;
		}
		x++;
	}
	y = 0;
	while (y <= j)
	{
		free(tokenlist->token[x][y].value);
		y++;
	}
}

void	malloc_failed(void)
{
	perror("Memory allocation failed");
	exit(EXIT_FAILURE);
}
