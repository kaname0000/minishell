/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_command_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:19:02 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/13 15:20:11 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

// //前後がスペースなしでくっついているか確認
// static int	check_both(t_tokenset *tokenset, int i, int j)
// {
// 	int	len;

// 	len = ft_strlen(tokenset->token[i + 1]->value);
// 	if (tokenset->input[j + len + 2] != ' ')
// 	{
// 		if (tokenset->input[j + len + 2] != '\'')
// 		{
// 			if (tokenset->input[j + len + 2] != '"')
// 			{
// 				if (tokenset->input[j + len + 2])
// 					return (SUCCESS);
// 			}
// 		}
// 	}
// 	return (FAILED);
// }

// //対象が結合すべきであるか判別
// static int	inspect_quote_edges(t_tokenset *tokenset, int i, int j)
// {
// 	if (tokenset->token[i]->type == TOK_SQUOTE_START
// 		|| tokenset->token[i]->type == TOK_DQUOTE_START)
// 	{
// 		if (!j || tokenset->input[j - 1] == ' ')
// 			return (NO_JOIN);
// 		else if (check_both(tokenset, i, j))
// 			return (BOTH);
// 		else
// 			return (FRONT);
// 	}
// 	else
// 	{
// 		if (j == tokenset->count - 1 || tokenset->input[j + 1] == ' '
// 			|| tokenset->input[j + 1] == '\0')
// 			return (NO_JOIN);
// 		else
// 			return (BACK);
// 	}
// }

// // tokenset->token から [start, start+minus) を削除
// void	remove_token(t_tokenset *tokenset, int start, int minus)
// {
// 	t_token	**new;
// 	int		j;
// 	int		k;

// 	new = (t_token **)malloc(sizeof(t_token *) * (tokenset->count - minus));
// 	if (!new)
// 		free_tokenset(tokenset, FAILED);
// 	j = 0;
// 	while (j < start)
// 	{
// 		new[j] = tokenset->token[j];
// 		j++;
// 	}
// 	k = 0;
// 	while (k < minus)
// 	{
// 		free(tokenset->token[start + k]->value);
// 		free(tokenset->token[start + k++]);
// 	}
// 	k = start + minus;
// 	while (k < tokenset->count)
// 		new[j++] = tokenset->token[k++];
// 	free(tokenset->token);
// 	tokenset->token = new;
// 	tokenset->count -= minus;
// }

// // quote 周りを削除・マージ
// static void	remove_quote_and_merge(t_tokenset *tokenset, int open, int key)
// {
// 	char	*inside;
// 	char	*new_value;
// 	int		i;

// 	if (key == BOTH)
// 		return (remove_quote_and_merge_ex(tokenset, open));
// 	inside = tokenset->token[open + 1]->value;
// 	if (key == FRONT)
// 		i = open - 1;
// 	else
// 		i = open + 3;
// 	new_value = ft_strjoin(tokenset->token[i]->value, inside);
// 	if (!new_value)
// 		free_tokenset(tokenset, FAILED);
// 	free(tokenset->token[i]->value);
// 	tokenset->token[i]->value = new_value;
// 	remove_token(tokenset, open, 3);
// 	i = 0;
// 	while (i < tokenset->count)
// 		tokenset->token[i++]->type = UNSIGNED;
// }

// // ec"ho"やecho"oo"に対応
// int	fix_command_token(t_tokenset *tokenset)
// {
// 	int		i;
// 	char	*value;
// 	int		count;
// 	int		pos;
// 	int		key;

// 	i = 0;
// 	while (i < tokenset->count)
// 	{
// 		value = tokenset->token[i]->value;
// 		if (value && (!ft_strcmp(value, "'") || !ft_strcmp(value, "\"")))
// 		{
// 			count = count_quote_in_input(tokenset, i, value);
// 			pos = check_input(tokenset->input, count, value);
// 			key = inspect_quote_edges(tokenset, i, pos);
// 			if (key != NO_JOIN)
// 			{
// 				reset_input(tokenset, i, pos, key);
// 				remove_quote_and_merge(tokenset, i, key);
// 				return (SUCCESS);
// 			}
// 		}
// 		i++;
// 	}
// 	return (FAILED);
// }

//前後がスペースなしでくっついているか確認
static int	check_both(t_tokenset *tokenset, int i, int j)
{
	int	len;

	len = ft_strlen(tokenset->token[i + 1]->value);
	if (tokenset->input[j + len + 2] != ' ')
	{
		if (tokenset->input[j + len + 2] != '\'')
		{
			if (tokenset->input[j + len + 2] != '"')
			{
				if (tokenset->input[j + len + 2])
					return (SUCCESS);
			}
		}
	}
	return (FAILED);
}

//対象が結合すべきであるか判別
static int	inspect_quote_edges(t_tokenset *tokenset, int i, int j)
{
	if (tokenset->token[i]->type == TOK_SQUOTE_START
		|| tokenset->token[i]->type == TOK_DQUOTE_START)
	{
		if (!j || tokenset->input[j - 1] == ' ')
			return (NO_JOIN);
		else if (check_both(tokenset, i, j))
			return (BOTH);
		else
			return (FRONT);
	}
	else
	{
		if (j == tokenset->count - 1 || tokenset->input[j + 1] == ' '
			|| tokenset->input[j + 1] == '\0')
			return (NO_JOIN);
		else
			return (BACK);
	}
}

// quoteや不要になったquoteの中身のtokenを削除
void	remove_token(t_tokenset *tokenset, int i, int minus)
{
	t_token	**new;
	int		j;
	int		k;

	new = (t_token **)malloc(sizeof(t_token *) * (tokenset->count - minus));
	if (!new)
		free_tokenset(tokenset, FAILED);
	j = 0;
	while (j < i)
	{
		new[j] = tokenset->token[j];
		j++;
	}
	k = 0;
	while (k < minus)
	{
		free(tokenset->token[i + k]->value);
		free(tokenset->token[i + k]);
		k++;
	}
	i += minus;
	while (j < tokenset->count - minus)
		new[j++] = tokenset->token[i++];
	free(tokenset->token);
	tokenset->token = new;
}

// quoteのtokenを削除しつつ、前後どちらかと合体させる
static void	remove_quote_and_merge(t_tokenset *tokenset, int i, int key)
{
	char	*new_value;
	int		n;

	if (key == BOTH)
		return (remove_quote_and_merge_ex(tokenset, i));
	if (!ft_strcmp(tokenset->token[i + 1]->value, "'")
		|| !ft_strcmp(tokenset->token[i + 1]->value, "\""))
		n = 2;
	else
		n = 1;
	new_value = ft_strjoin(tokenset->token[i - 1]->value, tokenset->token[i
			+ n]->value);
	if (!new_value)
		free_tokenset(tokenset, FAILED);
	if (key == BACK)
		i += 2;
	free(tokenset->token[i + n - 2]->value);
	tokenset->token[i + n - 2]->value = new_value;
	if (key == BACK)
		i -= 4;
	remove_token(tokenset, i + n - 1, 3);
	tokenset->count -= 3;
	i = 0;
	while (i < tokenset->count)
		tokenset->token[i++]->type = UNSIGNED;
}

// ec"ho"やecho"oo"に対応
int	fix_command_token(t_tokenset *tokenset)
{
	int	i;
	int	j;
	int	count;
	int	key;

	i = 0;
	while (i < tokenset->count)
	{
		if (!ft_strcmp(tokenset->token[i]->value, "'")
			|| !ft_strcmp(tokenset->token[i]->value, "\""))
		{
			count = count_quote_in_input(tokenset, i,
					tokenset->token[i]->value);
			j = check_input(tokenset->input, count, tokenset->token[i]->value);
			key = inspect_quote_edges(tokenset, i, j);
			if (key)
			{
				reset_input(tokenset, i, j, key);
				remove_quote_and_merge(tokenset, i, key);
				return (SUCCESS);
			}
		}
		i++;
	}
	return (FAILED);
}
