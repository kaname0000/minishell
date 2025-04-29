/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_new_value_in_quote.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:00:45 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/29 22:03:30 by yookamot         ###   ########.fr       */
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
int	search_quote(t_tokenset *tokenset, int x)
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
char	*make_new_value(char *input, int a, int b)
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

// 空文字列もしくはスペースのみの文字列を生成する
char	*make_new_empty_value(t_tokenset *tokenset, int i)
{
	int		j;
	char	quote;
	int		count;
	char	*value;

	j = search_quote(tokenset, i);
	quote = tokenset->input[j];
	j++;
	count = 0;
	while (tokenset->input[j] == ' ')
	{
		count++;
		j++;
	}
	value = (char *)malloc(sizeof(char) * (count + 1));
	if (!value)
		free_tokenset(tokenset, FAILED);
	if (count)
		ft_memset(value, ' ', count);
	value[count] = '\0';
	return (value);
}
