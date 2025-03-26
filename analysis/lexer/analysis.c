/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:56:35 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/26 17:27:47 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//字句解析と構文解析
t_tokenset	*analysis(char *input)
{
	t_tokenlist	*tokenlist;
	t_tokenset	*tokenset;

	tokenlist = (t_tokenlist *)malloc(sizeof(t_tokenlist));
	if (!tokenlist)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	tokenset = lexical_analysis(input, tokenlist);
	// syntax_analysis(tokenlist);
	return (tokenset);
}
