/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:56:35 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/16 19:43:40 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"

//字句解析と構文解析
t_tokenset	*analysis(char *input, t_mini *mini)
{
	t_tokenlist	*tokenlist;
	t_tokenset	*tokenset;

	if (!input)
		return (NULL);
	tokenlist = (t_tokenlist *)malloc(sizeof(t_tokenlist));
	if (!tokenlist)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	tokenlist->input = input;
	tokenlist->sflag = NULL;
	tokenlist->dflag = NULL;
	tokenset = lexical_analysis(tokenlist, mini);
	tokenset->input = input;
	if (!syntax_analysis(tokenset))
		return (NULL);
	return (tokenset);
}
