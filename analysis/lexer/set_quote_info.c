/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_quote_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:09:00 by okamotoyota       #+#    #+#             */
/*   Updated: 2025/03/23 20:22:01 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	set_quote_after_squote(t_token *token)
{
	if (!ft_strcmp(token->value, "'"))
		token->type = TOK_SQUOTE_END;
	else
		token->squote = 1;
}

static void	set_quote_after_dquote(t_token *token)
{
	if (!ft_strcmp(token->value, "\""))
		token->type = TOK_DQUOTE_END;
	else
		token->dquote = 1;
}

static void	set_quote_after_backslash(t_token *token, t_token *pre_token,
		t_token *pre_pre_token)
{
	if (pre_pre_token->squote)
	{
		pre_token->squote = 1;
		pre_token->dquote = 0;
		token->squote = 1;
		return ;
	}
	if (pre_pre_token->dquote)
	{
		pre_token->squote = 0;
		token->dquote = 1;
		token->type = TOK_DQUOTE_IN;
		if (!ft_strcmp(token->value, "\"") || !ft_strcmp(token->value, "$")
				|| !ft_strcmp(token->value, "`"))
			pre_token->dquote = 0;
		else
		{
			pre_token->dquote = 0;
			pre_token->type = TOK_DQUOTE_IN;
			token->type = TOK_DQUOTE_IN;
		}
		return ;
	}
}

void	set_quote_info(t_token *token, t_token *pre_token,
		t_token *pre_pre_token)
{
	if (pre_token && pre_token->squote)
	{
		set_quote_after_squote(token);
		return ;
	}
	else if (pre_token && pre_token->dquote)
	{
		set_quote_after_dquote(token);
		return ;
	}
	else if (pre_token && pre_token->type == TOK_BACKSLASH)
	{
		if (pre_pre_token && pre_pre_token->type == TOK_BACKSLASH)
			return ;
		else if (pre_pre_token && pre_pre_token->type != TOK_BACKSLASH)
		{
			set_quote_after_backslash(token, pre_token, pre_pre_token);
			return ;
		}
	}
	else
	{
		if (!ft_strcmp(token->value, "'"))
		{
			token->type = TOK_SQUOTE_START;
			token->squote = 1;
			return ;
		}
		else if (!ft_strcmp(token->value, "\""))
		{
			token->type = TOK_DQUOTE_START;
			token->dquote = 1;
		}
	}
}
