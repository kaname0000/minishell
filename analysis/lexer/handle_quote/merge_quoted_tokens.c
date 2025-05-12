/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_quoted_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 23:00:40 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/12 21:37:49 by yookamot         ###   ########.fr       */
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

static int	return_key(t_tokenset *tokenset, int i, int end)
{
	int	key;

	if (end == i + 1 && !ft_strchr(tokenset->token[end]->value, ' '))
	{
		handle_empty_in_quote(tokenset, i);
		key = SUCCESS;
	}
	else if (join_token(tokenset, i, end)
		|| handle_single_token_with_space(tokenset, i))
		key = SUCCESS;
	else
		key = FAILED;
	return (key);
}

// ── 3) merge_quoted_tokens の書き換え ──
int	merge_quoted_tokens(t_tokenset *tokenset)
{
	int	i;
	int	key;
	int	end;

	i = 0;
	key = 0;
	while (i < tokenset->count)
	{
		if (tokenset->token[i]->type == 7 || tokenset->token[i]->type == 10)
		{
			end = i + 1;
			while (end < tokenset->count
				&& tokenset->token[end]->type != TOK_SQUOTE_END
				&& tokenset->token[end]->type != TOK_DQUOTE_END)
				end++;
			if (end >= tokenset->count)
				break ;
			if (return_key(tokenset, i, end))
				add_quote(tokenset);
			i = -1;
		}
		i++;
	}
	return (key);
}
