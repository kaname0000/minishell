/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_quote_flag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:15:40 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/11 18:42:04 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// 0文字目の処理
static void	make_quote_flag_ex0(t_tokenlist *tokenlist)
{
	if (tokenlist->input[0] == '\'')
		tokenlist->sflag[0] = 1;
	else if (tokenlist->input[0] == '"')
		tokenlist->dflag[0] = 1;
}

// 0文字目以外の処理
static void	make_quote_flag_ex1(t_tokenlist *tokenlist, int i, char quote)
{
	if (quote == '\'')
	{
		if (!tokenlist->dflag[i - 1] && !tokenlist->sflag[i - 1])
			tokenlist->sflag[i] = 1;
		else if (tokenlist->dflag[i - 1])
			tokenlist->dflag[i] = 1;
	}
	else if (quote == '"')
	{
		if (!tokenlist->dflag[i - 1] && !tokenlist->sflag[i - 1])
			tokenlist->dflag[i] = 1;
		else if (tokenlist->sflag[i - 1])
			tokenlist->sflag[i] = 1;
	}
	else
	{
		tokenlist->sflag[i] = tokenlist->sflag[i - 1];
		tokenlist->dflag[i] = tokenlist->dflag[i - 1];
	}
}

// quoteが閉じられていなかった場合、修正する。
static int	fix_quote_flag(t_tokenlist *tokenlist, int *flag)
{
	int	i;

	i = ft_strlen(tokenlist->input) - 1;
	while (flag[i])
	{
		flag[i] = 0;
		i--;
	}
	return (i);
}

// quoteのフラグ配列作成、返り値は修正した先頭、次の呼び出しではそこからスタートする。
int	make_quote_flag(t_tokenlist *tokenlist, int i)
{
	int	j;

	while (tokenlist->input[i])
	{
		if (!i)
			make_quote_flag_ex0(tokenlist);
		else
			make_quote_flag_ex1(tokenlist, i, tokenlist->input[i]);
		i++;
	}
	j = 0;
	if (tokenlist->sflag[i - 1])
		j = fix_quote_flag(tokenlist, tokenlist->sflag);
	else if (tokenlist->dflag[i - 1])
		j = fix_quote_flag(tokenlist, tokenlist->dflag);
	return (j);
}
