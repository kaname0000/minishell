/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:05:30 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/24 18:56:27 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_redirect(t_tokenset *tokenset, int i)
{
	int	pre;
	int	cur;
	int	next;

	cur = tokenset->token[i]->type;
	if (cur == TOK_REDIR_IN || cur == TOK_REDIR_OUT || cur == TOK_REDIR_APPEND
		|| cur == TOK_HEREDOC)
	{
		if (i)
		{
			pre = tokenset->token[i - 1]->type;
			if (pre != TOK_WORD && pre != TOK_BUILTIN && pre != TOK_SQUOTE_IN
				&& pre != TOK_DQUOTE_IN && pre != TOK_PIPE)
				return (parser_error(tokenset, tokenset->token[i]->value));
		}
		if (i != tokenset->count - 1)
		{
			next = tokenset->token[i + 1]->type;
			if (next != TOK_WORD && next != TOK_BUILTIN && next != TOK_SQUOTE_IN
				&& next != TOK_DQUOTE_IN)
				return (parser_error(tokenset, tokenset->token[i + 1]->value));
		}
	}
	return (SUCCESS);
}
