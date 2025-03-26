/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:08:38 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/26 17:05:48 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	process_token(t_token *token)
{
	static t_token	*pre_token;
	static t_token	*pre_pre_token;

	if (token->count == 1)
	{
		set_quote_info(token, pre_token, pre_pre_token);
		get_tokentype(token, pre_token);
		if (pre_token && pre_pre_token)
			pre_pre_token = pre_token;
		if (token)
			pre_token = token;
	}
}

static void	traverse_tokens(t_token *token)
{
	int	i;

	process_token(token);
	if (token->count > 1)
	{
		i = 0;
		while (i < token->count)
		{
			traverse_tokens(token->split_token[i]);
			i++;
		}
	}
}

void	traverse_token_list(t_tokenlist *tokenlist)
{
	int	i;
	int	j;

	i = 0;
	while (i < tokenlist->set_count)
	{
		j = 0;
		while (j < tokenlist->token_count[i])
		{
			traverse_tokens(tokenlist->token[i][j]);
			j++;
		}
		i++;
	}
}
