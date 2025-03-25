/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 01:04:00 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/26 01:04:02 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// 字句解析
void	lexical_analysis(char *input, t_tokenlist *tokenlist)
{
	int			i;
	int			j;
	t_tokenset	*tokenset;

	// t_tokenset	*tokenset;
	get_tokens(input, tokenlist);
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
	// //トークンリストを扱いやすい形に
	// tokenset = reshape_tokenlist(tokenlist);
	// // echo "hello     world"のような形に対応
	// check_space_in_quote(input, tokenlist);
}

//各関数内でinputをfreeできてないかな