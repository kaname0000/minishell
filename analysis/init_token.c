/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:42:30 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/06 14:28:25 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"

//文字列中に指定の文字が何文字あるか数える
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

int	init_token(t_tokenlist *tokenlist, char *input)
{
	int	i;
	int	count;

	i = 0;
	tokenlist->set_count = count_letter(input, '\n');
	tokenlist->size = (int *)malloc((sizeof(int) * tokenlist->set_count));
	tokenlist->token = (t_token **)malloc(sizeof(t_token *)
			* tokenlist->set_count);
	if (!tokenlist->size || !tokenlist->token)
		return (FAILED);
	while (i < tokenlist->set_count)
	{
		count = 0;
		while (input[count] != '\n')
			count++;
	}
}
