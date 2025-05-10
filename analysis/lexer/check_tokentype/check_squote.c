/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_squote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 03:25:14 by okamotoyota       #+#    #+#             */
/*   Updated: 2025/05/10 14:43:49 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

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
			if (token->dquote)
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
	symbol = ft_strdup("'");
	if (!symbol)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	split_token(tokenlist, symbol, token, count);
	free(symbol);
	if (token->type != TOK_SPLIT)
		return (FAILED);
	return (SUCCESS);
}
