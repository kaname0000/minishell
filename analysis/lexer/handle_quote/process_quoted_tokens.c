/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quoted_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 23:00:40 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/18 00:44:31 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

// inputの何文字目が対象のクオーテーションマークかを返す
static int	search_quote_in_input(t_tokenset *tokenset, int count, char quote)
{
	int	i;

	i = 0;
	while (tokenset->input[i])
	{
		if (tokenset->input[i] == quote)
			count--;
		if (!count)
			return (i);
		i++;
	}
	return (FAILED);
}

//探すクオーテーションマークが何個目のクオーテーションマークかカウントし、inputの何文字目かを返す
static int	search_quote(t_tokenset *tokenset, int x)
{
	int		i;
	int		j;
	char	quote;
	int		count;

	i = 0;
	if (tokenset->token[x]->type == TOK_SQUOTE_START
		|| tokenset->token[x]->type == TOK_SQUOTE_END)
		quote = '\'';
	else
		quote = '"';
	count = 0;
	while (i < x)
	{
		j = 0;
		while (tokenset->token[i]->value[j])
		{
			if (tokenset->token[i]->value[j] == quote)
				count++;
			j++;
		}
		i++;
	}
	return (search_quote_in_input(tokenset, count + 1, quote));
}

//クオーテーションマーク配下の文字列を一つにまとめる
static char	*make_new_value(char *input, int a, int b)
{
	char	*new;
	int		i;

	new = (char *)malloc(sizeof(char) * (b - a));
	if (!new)
		return (NULL);
	i = 0;
	a++;
	while (i < b - a)
	{
		new[i] = input[a + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

// new_valueをもとにtokensetを更新する
static void	reshape_tokenset(t_tokenset *tokenset, int start, int end)
{
	t_token	**new_token;
	int		i;
	int		j;

	tokenset->count = tokenset->count - end + start + 1;
	new_token = (t_token **)malloc(sizeof(t_token *) * tokenset->count);
	if (!new_token)
		free_tokenset(tokenset, FAILED);
	i = 0;
	while (i <= start)
	{
		new_token[i] = tokenset->token[i];
		i++;
	}
	j = 0;
	while (i + j < end - 1)
	{
		free(tokenset->token[i + j]->value);
		free(tokenset->token[i + j]);
		j++;
	}
	while (i < tokenset->count)
		new_token[i++] = tokenset->token[end++];
	free(tokenset->token);
	tokenset->token = new_token;
}

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

// quoteに囲われた文字列を一つのトークンにまとめる、まとめるものがなかったらFAILED
static int	reshape_token_in_quote(t_tokenset *tokenset)
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
			if (join_token(tokenset, i, end)
				|| handle_single_token_with_space(tokenset, i))
				return (SUCCESS);
		}
		i++;
	}
	return (FAILED);
}

void	process_quoted_tokens(t_tokenset *tokenset)
{
	int	key;

	key = SUCCESS;
	while (key)
		key = reshape_token_in_quote(tokenset);
}
