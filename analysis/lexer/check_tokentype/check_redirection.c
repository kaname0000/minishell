/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamotoyota <okamotoyota@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:48:33 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/17 10:00:04 by okamotoyota      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_tokentype.h"

static int	count_redirection(t_token *token, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token->value[i])
	{
		if (token->value[i] == c && !(i && token->value[i - 1] == c)
			&& token->value[i + 1] != c)
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

int	check_redirection(t_token *token, int c, t_tokenlist *tokenlist)
{
	int		count;
	char	*symbol;

	count = count_redirection(token, c);
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
