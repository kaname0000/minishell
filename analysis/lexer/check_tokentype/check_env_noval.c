/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_noval.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:28:22 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/25 18:07:21 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

static int	count_noval(t_token *token, char *noval)
{
	int	i;
	int	j;

	i = 0;
	if (token->squote)
		return (FAILED);
	while (token->value[i])
	{
		j = 0;
		while (j < 6 && token->value[i + j] == noval[j])
			j++;
		if (j == 6)
			return (SUCCESS);
		i++;
	}
	return (FAILED);
}

int	check_env_noval(t_token *token, t_tokenlist *tokenlist)
{
	char	*symbol;

	symbol = ft_strdup("$NOVAL");
	if (!symbol)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	if (!count_noval(token, symbol))
		return (free(symbol), FAILED);
	split_token(tokenlist, symbol, token, 1);
	free(symbol);
	if (token->type != TOK_SPLIT)
		return (FAILED);
	return (SUCCESS);
}
