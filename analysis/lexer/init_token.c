/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamotoyota <okamotoyota@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:53:09 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/17 17:58:43 by okamotoyota      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	init_token(t_tokenlist *tokenlist)
{
	int	i;
	int	j;

	i = 0;
	while (i < tokenlist->set_count)
	{
		j = 0;
		while (j < tokenlist->token_count[i])
		{
			tokenlist->token[i][j]->type = UNSIGNED;
			tokenlist->token[i][j]->count = 1;
			tokenlist->token[i][j]->squote = 0;
			tokenlist->token[i][j]->dquote = 0;
			j++;
		}
		i++;
	}
}
