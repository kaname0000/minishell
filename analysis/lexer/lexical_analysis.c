/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 01:04:00 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/16 20:10:32 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// 字句解析
t_tokenset	*lexical_analysis(t_tokenlist *tokenlist, t_mini *mini)
{
	int			i;
	int			j;
	t_tokenset	*tokenset;

	process_env_var(tokenlist, mini);
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
	tokenset = reshape_tokenlist(tokenlist);
	set_tokentype(tokenset);
	while (check_unclosed_quote(tokenset))
		set_tokentype(tokenset);
	process_quoted_tokens(tokenset);
	return (tokenset);
}
