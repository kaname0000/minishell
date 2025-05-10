/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokenset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:01:57 by okaname           #+#    #+#             */
/*   Updated: 2025/05/10 13:49:37 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	free_tokenset(t_tokenset *tokenset, int key)
{
	int	i;

	if (!tokenset)
		return ;
	i = 0;
	while (i < tokenset->count)
	{
		free(tokenset->token[i]->value);
		free(tokenset->token[i]);
		i++;
	}
	free(tokenset->token);
	free(tokenset->input);
	free(tokenset);
	if (!key)
		malloc_failed();
}
