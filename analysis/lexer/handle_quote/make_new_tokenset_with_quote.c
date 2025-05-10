/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_new_tokenset_with_quote.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:40:23 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/10 20:22:29 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

//前後とクオーテーションマークを結合したかの判定
static int	check_quote_neighbors(t_tokenset *tokenset, int j)
{
	if (!j && tokenset->input[j + 1] != ' ')
		return (BACK);
	if (j && tokenset->input[j - 1] == ' ' && ft_strlen(tokenset->input) - j > 1
		&& tokenset->input[j + 1] != ' ')
		return (BACK);
	if (j && tokenset->input[j - 1] != ' ' && ((ft_strlen(tokenset->input)
				- j > 1 && tokenset->input[j + 1] == ' ')
			|| ft_strlen(tokenset->input) - j == 1))
		return (FRONT);
	if (j && tokenset->input[j - 1] != ' ' && ft_strlen(tokenset->input) - j > 1
		&& tokenset->input[j + 1] != ' ')
		return (BOTH);
	return (NO_JOIN);
}

//クオーテーションマークを適切にstrjoinする
static int	make_new_value_with_quote(t_tokenset *tokenset, int i, int key)
{
	char	*new;

	if (key == FRONT || key == BOTH)
	{
		tokenset->count--;
		new = ft_strjoin(tokenset->token[i - 1]->value,
				tokenset->token[i]->value);
		if (!new)
			return (FAILED);
		free(tokenset->token[i]->value);
		tokenset->token[i]->value = new;
	}
	if (key == BACK || key == BOTH)
	{
		tokenset->count--;
		new = ft_strjoin(tokenset->token[i]->value, tokenset->token[i
				+ 1]->value);
		if (!new)
			return (FAILED);
		free(tokenset->token[i]->value);
		tokenset->token[i]->value = new;
	}
	return (SUCCESS);
}

// tokensetをreshapeする
static int	reshape_tokenset(t_tokenset *tokenset, int i, int key)
{
	t_token	**new_token;
	int		k;

	new_token = (t_token **)malloc(sizeof(t_token *) * tokenset->count);
	if (!new_token)
		return (FAILED);
	k = 0;
	while (k < i)
	{
		if (k == i - 1 && key != BACK)
			break ;
		new_token[k] = tokenset->token[k];
		k++;
	}
	new_token[k] = tokenset->token[i];
	k++;
	i++;
	if (key != FRONT)
		i++;
	while (k < tokenset->count)
		new_token[k++] = tokenset->token[i++];
	free(tokenset->token);
	tokenset->token = new_token;
	return (SUCCESS);
}

static void	free_left_and_right(char *orig, t_token *left, t_token *right)
{
	free(orig);
	if (left)
	{
		free(left->value);
		free(left);
	}
	if (right)
	{
		free(right->value);
		free(right);
	}
}

// クオートで閉じられていない場合、tokensetを作り直す
int	make_new_tokenset_with_quote(t_tokenset *tokenset, int i, int j)
{
	int		key;
	char	*orig;
	t_token	*left;
	t_token	*right;

	left = NULL;
	right = NULL;
	key = check_quote_neighbors(tokenset, j);
	if (!key)
		return (tokenset->token[i]->type = TOK_WORD, FAILED);
	orig = ft_strdup(tokenset->token[i]->value);
	if (!orig)
		free_tokenset(tokenset, FAILED);
	if (key == FRONT || key == BOTH)
		left = tokenset->token[i - 1];
	if (key == BACK || key == BOTH)
		right = tokenset->token[i + 1];
	if (!make_new_value_with_quote(tokenset, i, key))
		return (free(orig), free_tokenset(tokenset, FAILED), FAILED);
	if (!ft_strcmp(orig, tokenset->token[i]->value))
		return (free(orig), FAILED);
	free_left_and_right(orig, left, right);
	if (!reshape_tokenset(tokenset, i, key))
		return (free_tokenset(tokenset, FAILED), FAILED);
	return (SUCCESS);
}
