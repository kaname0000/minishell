/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:05:30 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/16 17:21:50 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_redirect(t_tokenset *tokenset, int i)
{
	if (tokenset->token[i]->type == TOK_REDIR_IN
		|| tokenset->token[i]->type == TOK_REDIR_OUT
		|| tokenset->token[i]->type == TOK_REDIR_APPEND
		|| tokenset->token[i]->type == TOK_HEREDOC)
	{
		if (i == tokenset->count - 1)
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
