/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unclosed_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 01:43:57 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/29 21:51:52 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

// QUOTE_INのまま終了したクオートの情報をリセット
static void	reset_quote_info(t_tokenset *tokenset)
{
	int	i;

	i = tokenset->count - 1;
	while (tokenset->token[i]->type != TOK_SQUOTE_START
		&& tokenset->token[i]->type != TOK_DQUOTE_START)
		i--;
	while (i < tokenset->count)
	{
		tokenset->token[i]->type = UNSIGNED;
		tokenset->token[i]->squote = 0;
		tokenset->token[i]->dquote = 0;
		i++;
	}
}

//何個目のクオート文字が対象かを返す。
int	count_quote_in_input(t_tokenset *tokenset, int i, char *quote)
{
	int	j;
	int	count;
	int	k;

	j = 0;
	count = 0;
	while (j < i)
	{
		k = 0;
		while (tokenset->token[j]->value[k])
		{
			if (tokenset->token[j]->value[k] == quote[0])
				count++;
			k++;
		}
		j++;
	}
	return (count + 1);
}

//クオート文字がinputの何文字目かを返す。
int	check_input(char *input, int count, char *value)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == value[0])
			count--;
		if (!count)
			return (i);
		i++;
	}
	return (FAILED);
}

static int	resolve_unclosed_quote(t_tokenset *tokenset)
{
	int	i;
	int	count;
	int	j;

	i = 0;
	while (i < tokenset->count)
	{
		if (tokenset->token[i]->type == UNSIGNED
			&& (!ft_strcmp(tokenset->token[i]->value, "'")
				|| !ft_strcmp(tokenset->token[i]->value, "\"")))
		{
			count = count_quote_in_input(tokenset, i,
					tokenset->token[i]->value);
			j = check_input(tokenset->input, count, tokenset->token[i]->value);
			if (make_new_tokenset_with_quote(tokenset, i, j))
				return (SUCCESS);
		}
		i++;
	}
	return (FAILED);
}

// quote未閉じの場合、対応する
int	check_unclosed_quote(t_tokenset *tokenset)
{
	int	key;

	if (!tokenset->token[tokenset->count - 1]->squote
		&& !tokenset->token[tokenset->count - 1]->dquote)
		return (FAILED);
	reset_quote_info(tokenset);
	key = SUCCESS;
	while (key)
		key = resolve_unclosed_quote(tokenset);
	return (SUCCESS);
}
