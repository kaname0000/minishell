/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dquote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 03:25:14 by okamotoyota       #+#    #+#             */
/*   Updated: 2025/05/08 20:58:02 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

static int	count_dquote(t_token *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token->value[i])
	{
		if (token->value[i] == '"')
		{
			count++;
			if (token->squote)
				break ;
			return (count);
		}
		i++;
	}
	return (FAILED);
}

int	check_dquote(t_token *token, t_tokenlist *tokenlist)
{
	int		count;
	char	*symbol;

	if (!ft_strcmp(token->value, "\""))
		return (SUCCESS);
	count = count_dquote(token);
	if (!count)
		return (FAILED);
	symbol = ft_strdup("\"");
	if (!symbol)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	split_token(tokenlist, symbol, token, count);
	if (token->type != TOK_SPLIT)
		return (FAILED);
	return (SUCCESS);
}
