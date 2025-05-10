/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_quoted_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 23:00:40 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/10 20:25:42 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

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
