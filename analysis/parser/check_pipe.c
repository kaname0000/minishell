/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:35:36 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/08 20:51:02 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_pipe(t_tokenset *tokenset, int i)
{
	int	pre;
	int	cur;
	int	next;

	cur = tokenset->token[i]->type;
	if (cur == TOK_PIPE)
	{
		if (!i || i == tokenset->count - 1)
			return (parser_error(tokenset, tokenset->token[i]->value));
		pre = tokenset->token[i - 1]->type;
		if (pre != TOK_WORD && pre != TOK_BUILTIN)
			return (parser_error(tokenset, tokenset->token[i]->value));
		next = tokenset->token[i + 1]->type;
		if (next != TOK_WORD && next != TOK_BUILTIN)
			return (parser_error(tokenset, tokenset->token[i + 1]->value));
	}
	return (SUCCESS);
}
