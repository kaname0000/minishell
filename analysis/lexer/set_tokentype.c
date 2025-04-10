/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokentype.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:07:03 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/05 00:53:14 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	set_tokentype(t_tokenset *tokenset)
{
	int		i;
	t_token	*pre;
	t_token	*next;

	i = 0;
	while (i < tokenset->count)
	{
		if (!i)
			pre = NULL;
		else
			pre = tokenset->token[i - 1];
		if (i < tokenset->count - 1)
			next = tokenset->token[i + 1];
		else
			next = NULL;
		if (tokenset->token[i]->type == UNSIGNED)
			get_quote_info(tokenset->token[i], pre);
		get_tokentype(tokenset->token[i], pre);
		i++;
	}
}
