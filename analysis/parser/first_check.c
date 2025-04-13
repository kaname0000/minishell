/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:51:06 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/08 20:09:26 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	first_check(t_tokenset *tokenset)
{
	if (tokenset->token[0]->type == TOK_PIPE)
		error_token(tokenset, tokenset->token[0]->value);
	if (tokenset->token[0]->type == TOK_BUILTIN
		|| tokenset->token[0]->type == TOK_WORD)
		make_command_node(tokenset);
	if (tokenset->token[0]->type == TOK_REDIR_IN
		|| tokenset->token[0]->type == TOK_REDIR_OUT
		|| tokenset->token[0]->type == TOK_REDIR_APPEND
		|| tokenset->token[0]->type == TOK_HEREDOC)
		hundle_redirect(tokenset, 0, tokenset->token[0]->type);
	if (tokenset->token[0]->type == TOK_SQUOTE_START
		|| tokenset->token[0]->type == TOK_DQUOTE_START)
		hundle_quote(tokenset);
	if (tokenset->token[0]->type == TOK_ENV_VAR)
		hundle_env_var(tokenset);
}
