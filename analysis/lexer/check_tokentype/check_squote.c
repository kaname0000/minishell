/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_squote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 03:25:14 by okamotoyota       #+#    #+#             */
/*   Updated: 2025/03/13 20:16:40 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_tokentype.h"

static int	count_squote(t_token *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\'')
		{
			count++;
			if (token->dquote[i])
				break ;
			if (i == 1 && token->value[i - 1] == '\\' && !token->squote[i - 1])
				break ;
			if (i > 1 && token->value[i - 1] == '\\' && token->value[i
				- 2] != '\\' && !token->squote[i - 1])
				break ;
			else
				return (count);
		}
		i++;
	}
	return (FAILED);
}

int	check_squote(t_token *token, t_tokenlist *tokenlist)
{
	int		count;
	char	*symbol;

	count = count_squote(token);
	if (!count)
		return (FAILED);
	symbol = (char *)malloc(sizeof(char) * 2);
	if (!symbol)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	symbol[0] = '\'';
	symbol[1] = '\0';
	split_token(tokenlist, symbol, token, count);
	if (token->type != TOK_SPLIT)
		return (FAILED);
	return (SUCCESS);
}
