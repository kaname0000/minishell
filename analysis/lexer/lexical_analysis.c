/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:08:50 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/14 13:11:00 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//字句解析
void	lexical_analysis(char *input, t_tokenlist *tokenlist)
{
	int	i;
	int	j;

	get_tokens(input, tokenlist);
	check_quote(tokenlist);
	init_token(tokenlist);
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
	traverse_token_list(tokenlist);
}
