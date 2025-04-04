/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hundle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:35:56 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/03 23:23:46 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	hundle_redir_out(t_tokenset *tokenset, int i)
{
	char	*file;

	if (tokenset->token[i + 1]->type != TOK_WORD && tokenset->token[i
		+ 1]->type != TOK_ENV_VAR && tokenset->token[i
		+ 1]->type != TOK_SQUOTE_START && tokenset->token[i
		+ 1]->type != TOK_DQUOTE_START)
		error_token(tokenset, tokenset->token[i + 1]->value);
	if (tokenset->token[i + 1]->type == TOK_WORD)
		file = tokenset->token[i + 1]->value;
	if (tokenset->token[i + 1]->type == TOK_ENV_VAR)
		file = getenv(tokenset->token[i + 2]->value);
	if (tokenset->token[i + 1]->type == TOK_SQUOTE_START || tokenset->token[i
		+ 1]->type == TOK_DQUOTE_START)
	{
		get_value_in_quote(tokenset, i + 1);
		file = tokenset->token[i + 2]->value;
	}
	if (access(tokenset->token[i + 1]->value, F_OK) == 0
		&& access(tokenset->token[i + 1]->value, W_OK) == -1)
		error_outfile_invalid(tokenset, tokenset->token[i + 1]->value);
	// fileは正常なリダイレクト先。正常な構文として登録
}

void	hundle_redirect(t_tokenset *tokenset, int i, int type)
{
	if (type == TOK_REDIR_OUT)
		hundle_redir_out(tokenset, i);
	if (type == TOK_REDIR_IN)
		hundle_redir_in(tokenset, i);
}
