/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_double_symbol.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:42:44 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/05 00:41:58 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_tokentype.h"

static int	count_double_symbol(t_token *token, char *symbol)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token->value[i])
	{
		if (token->value[i] == symbol[0] && token->value[i + 1] == symbol[1])
		{
			count++;
			if (token->squote || token->dquote)
				break ;
			else
				return (count);
		}
		i++;
	}
	return (FAILED);
}

//２文字の指定の文字列が含まれたvalueの場合、splitする
int	check_double_symbol(t_token *token, char *symbol, t_tokenlist *tokenlist)
{
	int		count;
	char	*str;

	count = count_double_symbol(token, symbol);
	if (!count)
		return (FAILED);
	str = ft_strdup(symbol);
	if (!str)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	split_token(tokenlist, str, token, count);
	if (token->type != TOK_SPLIT)
		return (FAILED);
	return (SUCCESS);
}
