/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_single_symbol.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:32:49 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/13 19:58:27 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_tokentype.h"

static int	count_signle_symbol(t_token *token, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token->value[i])
	{
		if (token->value[i] == c)
		{
			count++;
			if (token->squote[i] || token->dquote[i] || (i != 0
					&& token->value[i - 1] == '\\'))
				break ;
			else
				return (count);
		}
		i++;
	}
	return (FAILED);
}

int	check_single_symbol(t_token *token, int c, t_tokenlist *tokenlist)
{
	int		count;
	char	*symbol;

	count = count_signle_symbol(token, c);
	if (!count)
		return (FAILED);
	symbol = (char *)malloc(sizeof(char) * 2);
	if (!symbol)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	symbol[0] = (char)c;
	symbol[1] = '\0';
	split_token(tokenlist, symbol, token, count);
	if (token->type != TOK_SPLIT)
		return (FAILED);
	return (SUCCESS);
}
