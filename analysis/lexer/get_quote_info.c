/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:09:00 by okamotoyota       #+#    #+#             */
/*   Updated: 2025/04/16 19:50:28 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	get_quote_info(t_token *token, t_token *pre)
{
	if (!pre)
	{
		if (!ft_strcmp(token->value, "'"))
		{
			token->squote = 1;
			token->type = TOK_SQUOTE_START;
		}
		if (!ft_strcmp(token->value, "\""))
		{
			token->dquote = 1;
			token->type = TOK_DQUOTE_START;
		}
	}
	else if (!ft_strcmp(token->value, "'"))
	{
		if (pre->dquote)
		{
			token->type = TOK_DQUOTE_IN;
			token->dquote = 1;
		}
		else if (pre->squote)
			token->type = TOK_SQUOTE_END;
		else
		{
			token->type = TOK_SQUOTE_START;
			token->squote = 1;
		}
	}
	else if (!ft_strcmp(token->value, "\""))
	{
		if (pre->squote)
		{
			token->type = TOK_SQUOTE_IN;
			token->squote = 1;
		}
		else if (pre->dquote)
			token->type = TOK_DQUOTE_END;
		else
		{
			token->type = TOK_DQUOTE_START;
			token->dquote = 1;
		}
	}
	else
	{
		if (pre->squote)
		{
			token->type = TOK_SQUOTE_IN;
			token->squote = 1;
		}
		else if (pre->dquote)
		{
			token->type = TOK_DQUOTE_IN;
			token->dquote = 1;
		}
	}
}
