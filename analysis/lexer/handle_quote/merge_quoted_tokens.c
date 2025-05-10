/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_quoted_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 23:00:40 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/10 18:29:20 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

// new_valueをもとにtokensetを更新する
// static void	reshape_tokenset(t_tokenset *tokenset, int start, int end)
// {
// 	t_token	**new_token;
// 	int		i;
// 	int		j;

// 	tokenset->count = tokenset->count - end + start + 1;
// 	new_token = (t_token **)malloc(sizeof(t_token *) * tokenset->count);
// 	if (!new_token)
// 		free_tokenset(tokenset, FAILED);
// 	i = 0;
// 	while (i <= start)
// 	{
// 		new_token[i] = tokenset->token[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (i + j < end - 1)
// 	{
// 		free(tokenset->token[i + j]->value);
// 		free(tokenset->token[i + j]);
// 		j++;
// 	}
// 	while (i < tokenset->count)
// 		new_token[i++] = tokenset->token[end++];
// 	free(tokenset->token);
// 	tokenset->token = new_token;
// }

static void	reshape_tokenset(t_tokenset *tokenset, int start, int end)
{
	int		new_count;
	t_token	**new_arr;
	int		i;
	int		j;

	new_count = tokenset->count - end + start - 1;
	new_arr = (t_token **)malloc(sizeof(t_token *) * new_count);
	if (!new_arr)
		free_tokenset(tokenset, FAILED);
	i = 0;
	while (i < start - 1)
	{
		new_arr[i] = tokenset->token[i];
		i++;
	}
	new_arr[i++] = tokenset->token[start];
	j = end + 1;
	while (j < tokenset->count)
		new_arr[i++] = tokenset->token[j++];
	j = start - 1;
	while (j <= end)
	{
		if (j != start)
		{
			free(tokenset->token[j]->value);
			free(tokenset->token[j]);
		}
		j++;
	}
	free(tokenset->token);
	tokenset->token = new_arr;
	tokenset->count = new_count;
}

// "hello world"に対応
static int	join_token(t_tokenset *tokenset, int start, int end)
{
	int		a;
	int		b;
	char	*new_value;

	if (end - start == 2)
		return (FAILED);
	a = search_quote(tokenset, start);
	b = search_quote(tokenset, end);
	new_value = make_new_value(tokenset->input, a, b);
	if (!new_value)
		free_tokenset(tokenset, FAILED);
	start++;
	free(tokenset->token[start]->value);
	tokenset->token[start]->value = new_value;
	reshape_tokenset(tokenset, start, end);
	return (SUCCESS);
}

// " hello"に対応
static int	handle_single_token_with_space(t_tokenset *tokenset, int i)
{
	int		j;
	int		k;
	int		l;
	char	*new_value;

	j = check_input(tokenset->input, count_quote_in_input(tokenset, i,
				tokenset->token[i]->value), tokenset->token[i]->value);
	k = check_input(tokenset->input, count_quote_in_input(tokenset, i + 2,
				tokenset->token[i + 2]->value), tokenset->token[i + 2]->value);
	if (tokenset->input[j + 1] != ' ' && tokenset->input[k - 1] != ' ')
		return (FAILED);
	l = 0;
	while (tokenset->token[i + 1]->value[l])
	{
		if (tokenset->token[i + 1]->value[l] == ' ')
			return (FAILED);
		l++;
	}
	new_value = make_new_value(tokenset->input, j, k);
	if (!new_value)
		free_tokenset(tokenset, FAILED);
	free(tokenset->token[i + 1]->value);
	tokenset->token[i + 1]->value = new_value;
	return (SUCCESS);
}

// "", "   "に対応
static void	handle_empty_in_quote(t_tokenset *tokenset, int i)
{
	t_token	**new;
	int		j;

	tokenset->count++;
	new = (t_token **)malloc(sizeof(t_token *) * tokenset->count);
	if (!new)
		free_tokenset(tokenset, FAILED);
	j = 0;
	while (j <= i)
	{
		new[j] = tokenset->token[j];
		j++;
	}
	new[j] = (t_token *)malloc(sizeof(t_token));
	if (!new[j])
		free_tokenset(tokenset, FAILED);
	make_new_empty_value(tokenset, new[j], i);
	if (tokenset->token[i++]->type == TOK_SQUOTE_START)
		new[j++]->type = TOK_SQUOTE_IN;
	else
		new[j++]->type = TOK_DQUOTE_IN;
	while (j < tokenset->count)
		new[j++] = tokenset->token[i++];
	free(tokenset->token);
	tokenset->token = new;
}

// quoteに囲われた文字列を一つのトークンにまとめる
int	merge_quoted_tokens(t_tokenset *tokenset)
{
	int	i;
	int	end;

	i = 0;
	while (i < tokenset->count)
	{
		if (tokenset->token[i]->type == TOK_SQUOTE_START
			|| tokenset->token[i]->type == TOK_DQUOTE_START)
		{
			end = i;
			while (tokenset->token[end]->type != TOK_SQUOTE_END
				&& tokenset->token[end]->type != TOK_DQUOTE_END)
				end++;
			if (end == i + 1)
			{
				handle_empty_in_quote(tokenset, i);
				return (SUCCESS);
			}
			if (join_token(tokenset, i, end)
				|| handle_single_token_with_space(tokenset, i))
				return (SUCCESS);
		}
		i++;
	}
	return (FAILED);
}
