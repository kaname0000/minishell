/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reshape_tokenlist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 01:03:47 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/26 01:03:48 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// split_tokenまで考慮してカウント
static int	count_split_token(t_token *token)
{
	int	count;
	int	i;

	count = 1;
	if (token->split_token == NULL || token->count == 0)
		return (count);
	i = 0;
	while (i < token->count)
	{
		count += count_split_token(token->split_token[i]);
		i++;
	}
	return (count);
}

// tokenの総数をカウント
static int	count_token(char *input, t_tokenlist *tokenlist)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (i < tokenlist->set_count)
	{
		j = 0;
		while (j < tokenlist->token_count[i])
		{
			count += count_split_token(tokenlist->token[i][j]);
			j++;
		}
		i++;
	}
	return (count);
}

//再帰的にsplit_tokenの中までカウントしていき、n番目のトークンを取得する
static t_token	*find_nth_token(t_token *token, int *count, int n)
{
	int		i;
	t_token	*result;

	if (*count == n)
		return (token);
	(*count)++;
	i = 0;
	while (i < token->count)
	{
		result = find_nth_token(token->split_token[i], count, n);
		if (result)
			return (result);
		i++;
	}
	return (NULL);
}

// n番目のトークンを取得する
static t_token	*get_nth_token(t_tokenlist *tokenlist, int n)
{
	int		i;
	int		j;
	int		count;
	t_token	*result;

	count = 0;
	i = 0;
	while (i < tokenlist->set_count)
	{
		j = 0;
		while (j < tokenlist->token_count[i])
		{
			result = find_nth_token(tokenlist->token[i][j], &count, n);
			if (result)
				return (result);
			j++;
		}
		i++;
	}
	return (NULL);
}

//新たにtokensetを用意し、一次元配列でトークンを管理
t_tokenset	*reshape_tokenlist(char *input, t_tokenlist *tokenlist)
{
	t_tokenset	*tokenset;
	int			n;

	tokenset = (t_tokenset *)malloc(sizeof(t_tokenset));
	if (!tokenset)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	tokenset->count = count_token(tokenlist);
	tokenset->token = (t_token **)malloc(sizeof(tokenset->count));
	if (!tokenset->token)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	n = 0;
	while (n < tokenset->count)
	{
		tokenset->token[n] = get_nth_token(tokenlist, n);
		n++;
	}
	free(tokenlist->token_count);
	free(tokenlist);
	tokenize_with_quotes(input, tokenset);
}
