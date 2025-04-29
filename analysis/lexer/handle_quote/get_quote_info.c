/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:09:00 by okamotoyota       #+#    #+#             */
/*   Updated: 2025/04/29 22:12:36 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

static void	get_quote_info1(t_token *token)
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

static void	get_quote_info2(t_token *token, t_token *pre)
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

static void	get_quote_info3(t_token *token, t_token *pre)
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

static void	get_quote_info4(t_token *token, t_token *pre)
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

void	get_quote_info(t_token *token, t_token *pre)
{
	if (!pre)
		get_quote_info1(token);
	else if (!ft_strcmp(token->value, "'"))
		get_quote_info2(token, pre);
	else if (!ft_strcmp(token->value, "\""))
		get_quote_info3(token, pre);
	else
		get_quote_info4(token, pre);
}
