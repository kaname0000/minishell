/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:24:53 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/14 12:30:04 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	malloc_flag_array(t_token *token, int k, int len, int start)
{
	int	i;

	token->split_token[k]->squote = (int *)malloc(sizeof(int) * len);
	if (!token->split_token[k]->squote)
		return (FAILED);
	token->split_token[k]->dquote = (int *)malloc(sizeof(int) * len);
	if (!token->split_token[k]->dquote)
		return (FAILED);
	i = 0;
	while (i < len)
	{
		token->split_token[k]->squote[i] = token->squote[start + i];
		token->split_token[k]->dquote[i] = token->dquote[start + i];
		i++;
	}
	return (SUCCESS);
}

void	remake_quote(t_tokenlist *tokenlist, t_token *token)
{
	int	k;
	int	len;
	int	start;

	k = 0;
	start = 0;
	while (k < token->count)
	{
		len = ft_strlen(token->split_token[k]->value);
		if (!malloc_flag_array(token, k, len, start))
			free_tokenlist(tokenlist, NULL, NULL, FAILED);
		start += len;
		k++;
	}
}
