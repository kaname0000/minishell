/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:17:11 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/09 22:09:51 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	**check_quote(char **array, int c)
{
	int	i;
	int	j;

	i = 0;
	while (array[i])
	{
		j = 0;
		if (array[i][0] == c && array[i][ft_strlen(array[i]) - 1] != c)
		{
		}
	}
}

char	**check_single_and_double_quote(char **array)
{
	if (!array)
		return (NULL);
	array = check_quote(array, '\'');
	if (!array)
		return (NULL);
	array = check_quote(array, '\"');
	return (array);
}
