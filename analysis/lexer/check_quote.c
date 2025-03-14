/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:26:44 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/13 19:41:20 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//各トークンのsquoteとdquoteのフラグ用配列を確保する
static void	malloc_flag_array(t_tokenlist *tokenlist, int i, int j)
{
	int	len;
	int	*squote;
	int	*dquote;

	if (!tokenlist->token[i][j]->value)
		return ;
	len = ft_strlen(tokenlist->token[i][j]->value);
	squote = (int *)malloc(sizeof(int) * len);
	if (!squote)
	{
		free_flag_array(tokenlist);
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	}
	dquote = (int *)malloc(sizeof(int) * len);
	if (!dquote)
	{
		free(squote);
		free_flag_array(tokenlist);
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	}
	tokenlist->token[i][j]->squote = squote;
	tokenlist->token[i][j]->dquote = dquote;
}

//前の文字のsquoteのflagを得る
static int	get_pre_sflag(t_tokenlist *tokenlist, int i, int j, int k)
{
	t_token	*token;

	if (k != 0)
		return (tokenlist->token[i][j]->squote[k - 1]);
	if (j != 0)
	{
		token = tokenlist->token[i][j - 1];
		return (token->squote[ft_strlen(token->value) - 1]);
	}
	if (i != 0)
	{
		token = tokenlist->token[i - 1][tokenlist->token_count[i - 1] - 2];
		return (token->squote[ft_strlen(token->value) - 1]);
	}
	return (0);
}

//前の文字のdquoteのflagを得る
static int	get_pre_dflag(t_tokenlist *tokenlist, int i, int j, int k)
{
	t_token	*token;

	if (k != 0)
		return (tokenlist->token[i][j]->dquote[k - 1]);
	if (j != 0)
	{
		token = tokenlist->token[i][j - 1];
		return (token->dquote[ft_strlen(token->value) - 1]);
	}
	if (i != 0)
	{
		token = tokenlist->token[i - 1][tokenlist->token_count[i - 1] - 2];
		return (token->dquote[ft_strlen(token->value) - 1]);
	}
	return (0);
}

//トークンの各文字がそれぞれのクォート配下かの情報を保存する
static void	get_quote_info(t_tokenlist *tokenlist, int i, int j, int k)
{
	int		pre_sflag;
	int		pre_dflag;
	char	cur_char;

	pre_sflag = get_pre_sflag(tokenlist, i, j, k);
	pre_dflag = get_pre_dflag(tokenlist, i, j, k);
	cur_char = tokenlist->token[i][j]->value[k];
	if (cur_char == '\'' && !pre_dflag)
		pre_sflag = !pre_sflag;
	if (cur_char == '"' && !pre_sflag)
		pre_dflag = !pre_dflag;
	tokenlist->token[i][j]->squote[k] = pre_sflag;
	tokenlist->token[i][j]->dquote[k] = pre_dflag;
}

void	check_quote(t_tokenlist *tokenlist)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < tokenlist->set_count)
	{
		j = 0;
		while (j < tokenlist->token_count[i] - 1)
		{
			malloc_flag_array(tokenlist, i, j);
			k = 0;
			while (k < (int)ft_strlen(tokenlist->token[i][j]->value))
			{
				get_quote_info(tokenlist, i, j, k);
				k++;
			}
			j++;
		}
		i++;
	}
}
