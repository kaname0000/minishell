/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_double_symbol.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamotoyota <okamotoyota@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:42:44 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/17 10:01:24 by okamotoyota      ###   ########.fr       */
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
			if (token->squote || token->dquote || (i != 0 && token->value[i
					- 1] == '\\'))
				break ;
			else
				return (count);
		}
		i++;
	}
	return (FAILED);
}

int	check_double_symbol(t_token *token, char *symbol, t_tokenlist *tokenlist)
{
	int	count;

	count = count_double_symbol(token, symbol);
	if (!count)
		return (FAILED);
	split_token(tokenlist, ft_strdup(symbol), token, count);
	if (token->type != TOK_SPLIT)
		return (FAILED);
	return (SUCCESS);
}
