/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_quoted_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 23:00:40 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/13 15:05:41 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

// "    hello"に対応
static int	handle_single_token_with_space(t_tokenset *tokenset, int i)
{
	int		start;
	int		end;
	int		l;
	char	*new_value;

	start = check_input(tokenset->input, count_quote_in_input(tokenset, i,
				tokenset->token[i]->value), tokenset->token[i]->value);
	end = check_input(tokenset->input, count_quote_in_input(tokenset, i + 2,
				tokenset->token[i + 2]->value), tokenset->token[i + 2]->value);
	if (tokenset->input[start + 1] != ' ' && tokenset->input[end - 1] != ' ')
		return (FAILED);
	l = 0;
	while (tokenset->token[i + 1]->value[l])
	{
		if (tokenset->token[i + 1]->value[l] == ' ')
			return (FAILED);
		l++;
	}
	new_value = make_new_value(tokenset->input, start, end);
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

static int	return_key(t_tokenset *tokenset, int start, int end)
{
	int	key;

	if (end == start + 1)
	{
		handle_empty_in_quote(tokenset, start);
		key = SUCCESS;
	}
	else if (join_token(tokenset, start, end)
		|| handle_single_token_with_space(tokenset, start))
		key = SUCCESS;
	else
		key = FAILED;
	if (key)
		add_quote(tokenset);
	return (key);
}

// "hello world"のような文字列を一つのトークンにまとめる
int	merge_quoted_tokens(t_tokenset *tokenset)
{
	int	i;
	int	key;
	int	end;

	i = 0;
	key = 0;
	while (i < tokenset->count)
	{
		if (tokenset->token[i]->type == TOK_SQUOTE_START
			|| tokenset->token[i]->type == TOK_DQUOTE_START)
		{
			end = i + 1;
			while (end < tokenset->count
				&& tokenset->token[end]->type != TOK_SQUOTE_END
				&& tokenset->token[end]->type != TOK_DQUOTE_END)
				end++;
			if (end >= tokenset->count)
				break ;
			if (return_key(tokenset, i, end))
				i--;
		}
		i++;
	}
	return (key);
}
