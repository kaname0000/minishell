/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_backslash_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:47:03 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/02 18:18:15 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	get_backslash_info(t_token *token, t_token *pre, t_token *next)
{
	if (ft_strcmp(token->value, "\\"))
		return ;
	if (!pre)
		token->type = TOK_BACKSLASH;
	if (pre->type == TOK_BACKSLASH)
	{
		token->type = TOK_DQUOTE_IN;
		token->squote = pre->squote;
		token->dquote = pre->dquote;
	}
	else if (pre->squote)
	{
		token->type = TOK_SQUOTE_IN;
		token->squote = 1;
	}
	else if (pre->dquote)
	{
		if (next && (!ft_strcmp(next->value, "$") || !ft_strcmp(next->value,
					"\"") || !ft_strcmp(next->value, "\\")))
		{
			token->type = TOK_BACKSLASH;
			token->dquote = 1;
			next->type = TOK_DQUOTE_IN;
			next->dquote = 1;
		}
		else
		{
			token->type = TOK_DQUOTE_IN;
			token->type = 1;
		}
	}
	else
		token->type = TOK_BACKSLASH;
}
