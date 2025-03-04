/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:42:30 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/04 20:47:13 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"

static int	count_letter(char *input, char c)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (input[i])
	{
		if (input[i] == c)
			count++;
		i++;
	}
	return (count);
}

t_tokenlist	*init_token(char *input)
{
	t_tokenlist *tokenlist;
	int i;
	int j;

	tokenlist = (t_tokenlist *)malloc(sizeof(t_tokenlist));
	if (!tokenlist)
		return (NULL);
	tokenlist->set_count = count_letter(input, '\n');
	i = 0;
	while (input[i])
	{
		if (input[i] == '\n')
	}
}