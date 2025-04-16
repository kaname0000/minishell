/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:35:36 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/16 17:21:39 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_pipe(t_tokenset *tokenset, int i)
{
	if (tokenset->token[i]->type == TOK_PIPE)
	{
		if (!i || i == tokenset->count - 1)
			return (parser_error(tokenset, tokenset->token[i]->value));
		else if (tokenset->token[i - 1]->type != TOK_WORD && tokenset->token[i
			- 1]->type != TOK_BUILTIN)
			return (parser_error(tokenset, tokenset->token[i]->value));
		else if (tokenset->token[i + 1]->type != TOK_WORD && tokenset->token[i
			+ 1]->type != TOK_BUILTIN)
			return (parser_error(tokenset, tokenset->token[i + 1]->value));
	}
	return (SUCCESS);
}
