/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokentype.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:02:03 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/16 19:22:03 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// tokenのvalueの中から、キーワードを探し、見つけた場合はsplitする
static void	search_keyword(t_token *token, t_tokenlist *tokenlist)
{
	if (check_single_symbol(token, '|', tokenlist))
		return ;
	if (check_double_symbol(token, "<<", tokenlist))
		return ;
	if (check_double_symbol(token, ">>", tokenlist))
		return ;
	if (check_redirection_out(token, tokenlist))
		return ;
	if (check_redirection_in(token, tokenlist))
		return ;
	if (check_squote(token, tokenlist))
		return ;
	if (check_dquote(token, tokenlist))
		return ;
}

// token_typeの割当
void	check_tokentype(t_token *token, t_tokenlist *tokenlist)
{
	int	i;

	if (!token || !token->value)
		return ;
	search_keyword(token, tokenlist);
	if (token->count > 1 && token->split_token)
	{
		i = 0;
		while (i < token->count)
		{
			if (token->split_token[i]->value)
				check_tokentype(token->split_token[i], tokenlist);
			i++;
		}
	}
}
