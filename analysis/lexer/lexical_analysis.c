/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 01:04:00 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/02 17:54:23 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// 字句解析
t_tokenset	*lexical_analysis(t_tokenlist *tokenlist)
{
	int			i;
	int			j;
	char		*input;
	t_tokenset	*tokenset;

	get_tokens(tokenlist);
	i = 0;
	while (i < tokenlist->set_count)
	{
		j = 0;
		while (j < tokenlist->token_count[i])
		{
			check_tokentype(tokenlist->token[i][j], tokenlist);
			j++;
		}
		i++;
	}
	input = ft_strdup(tokenlist->input);
	if (!input)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	tokenset = reshape_tokenlist(tokenlist, input);
	set_tokentype(tokenset);
	tokenize_with_quotes(tokenset, input);
	free(input);
	return (tokenset);
}
