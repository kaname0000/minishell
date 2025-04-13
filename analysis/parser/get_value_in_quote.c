/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value_in_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 23:00:40 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/05 02:04:03 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// valueの中にstrが何個含まれているかをカウント
static int	search_str_in_value(char *value, char *str)
{
	int		count;
	char	*temp;

	count = 0;
	temp = ft_strstr(value, str);
	while (temp)
	{
		count++;
		temp = ft_strstr(temp + 1, str);
	}
	return (count);
}

// tokensetの中から見つけたいワードを探し、何番目が今回狙っていたワードか返す
static int	search_str_in_token(t_tokenset *tokenset, char *str, int i)
{
	int	count;
	int	j;

	count = 0;
	j = 0;
	while (j <= i)
	{
		count += search_str_in_value(tokenset->token[j]->value, str);
		j++;
	}
	return (count);
}

// inputの中から見つけたいワードを探し、先頭ポインタを返す
static char	*search_str_in_input(char *input, char *str, int count)
{
	char	*result;

	result = ft_strstr(input, str);
	count--;
	while (count > 0)
	{
		result = ft_strstr(result + 1, str);
		count--;
	}
	return (result);
}

//クオート配下の文字列にスペース文字が含まれているかチェック
static int	find_space(char *start, char *end)
{
	while (start != end)
	{
		if (*start == ' ')
			return (SUCCESS);
		start++;
	}
	return (FAILED);
}

//クオート配下の文字列をvalueとして持つトークンを作成
static t_token	*make_new_token(char *start, char *end, int type)
{
	t_token	*new_token;
	char	*new_value;
	int		i;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_value = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!new_value)
		return (free(new_token), NULL);
	i = 0;
	while (i < end - start)
	{
		new_value[i] = start[i];
		i++;
	}
	new_value[i] = '\0';
	new_token->value = new_value;
	if (type == TOK_DQUOTE_START)
		new_token->type = TOK_DQUOTE_IN;
	if (type == TOK_SQUOTE_START)
		new_token->type = TOK_SQUOTE_IN;
	return (new_token);
}

//新たなトークンをtokensetに含め、不要になったトークンを削除する
static int	reshape_tokenset(t_tokenset *tokenset, int i, int j,
		t_token *new_token)
{
	t_token	**temp;
	int		k;
	int		cut;

	tokenset->count = tokenset->count - j + 1;
	temp = (t_token **)malloc(sizeof(t_token *) * (tokenset->count));
	if (!temp)
		return (FAILED);
	k = 0;
	cut = 0;
	while (k < tokenset->count)
	{
		if (k == i)
		{
			temp[k] = new_token;
			cut = j - 1;
		}
		else
			temp[k] = tokenset->token[k + cut];
		k++;
	}
	k = 0;
	while (k < j)
	{
		free(tokenset->token[i + k]->value);
		free(tokenset->token[i + k]);
		k++;
	}
	free(tokenset->token);
	tokenset->token = temp;
	return (SUCCESS);
}

static int	search_str(t_tokenset *tokenset, int i)
{
	int		count;
	char	*start;
	char	*end;
	int		j;
	t_token	*new_token;

	count = search_str_in_token(tokenset, tokenset->token[i]->value, i);
	start = search_str_in_input(tokenset->input, tokenset->token[i]->value,
			count);
	j = 1;
	while (i + j < tokenset->count && (tokenset->token[i
			+ j]->type == TOK_DQUOTE_IN || tokenset->token[i
			+ j]->type == TOK_SQUOTE_IN))
		j++;
	count = search_str_in_token(tokenset, tokenset->token[i + j]->value, i + j);
	end = search_str_in_input(tokenset->input, tokenset->token[i + j]->value,
			count);
	if (find_space(start, end) && (tokenset->token[i + 1]->type == TOK_DQUOTE_IN
			|| tokenset->token[i + 1]->type == TOK_SQUOTE_IN))
	{
		new_token = make_new_token(start, end, tokenset->token[i - 1]->type);
		if (!new_token)
			free_tokenset(tokenset, FAILED);
		new_token->value = expand_env_var(new_token->value);
		if (!new_token->value)
		{
			free(new_token);
			free_tokenset(tokenset, FAILED);
		}
		if (!reshape_tokenset(tokenset, i, j, new_token))
		{
			free(new_token->value);
			free(new_token);
			free_tokenset(tokenset, FAILED);
		}
		return (SUCCESS);
	}
	return (FAILED);
}

// "hello   world  "のようなパターンに対応
void	tokenize_with_quotes(t_tokenset *tokenset)
{
	int	i;

	i = 0;
	while (i < tokenset->count)
	{
		while (i < tokenset->count)
		{
			if (i && (tokenset->token[i - 1]->type == TOK_DQUOTE_START
					|| tokenset->token[i - 1]->type == TOK_SQUOTE_START))
			{
				if (search_str(tokenset, i))
				{
					i = 0;
					break ;
				}
			}
			i++;
		}
	}
}

// quoteに囲われた文字列を返す
char	*get_value_in_quote(t_tokenset *tokenset, int i)
{
	search_str(tokenset, i + 1);
}
