/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:56:35 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/10 18:31:04 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//字句解析と構文解析
t_tokenset	*analysis(char *input)
{
	t_tokenlist	*tokenlist;
	t_tokenset	*tokenset;

	if (!input)
		return (NULL);
	tokenlist = (t_tokenlist *)malloc(sizeof(t_tokenlist));
	if (!tokenlist)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	tokenlist->input = input;
	tokenset = lexical_analysis(tokenlist);
	tokenset->input = input;
	// syntax_analysis(tokenset, input);
	return (tokenset);
}
