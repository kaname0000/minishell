/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 01:59:24 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/26 14:58:45 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// １つめのvalue作る
static char	*get_new_pre_value(const char *s1, const char *s2, int count)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s1[i + j] == s2[j] && s2[j])
			j++;
		if (!s2[j])
			count--;
		if (!count)
			break ;
		i++;
	}
	if (!i)
		return (ft_strdup(""));
	new = (char *)malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new[j] = s1[j];
		j++;
	}
	new[j] = '\0';
	return (new);
}

// ３つめのvalue作る
static char	*make_post_value(const char *s, int i)
{
	char	*new;
	int		j;

	new = (char *)malloc(sizeof(char) * (ft_strlen(s) - i + 1));
	if (!new)
		return (NULL);
	j = 0;
	while (s[i])
	{
		new[j] = s[i];
		j++;
		i++;
	}
	new[j] = '\0';
	return (new);
}

// ３つめのvalueつくる
static char	*get_new_post_value(const char *s1, const char *s2, int count)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s1[i + j] == s2[j] && s2[j])
			j++;
		if (!s2[j])
			count--;
		if (!count)
			return (make_post_value(s1, i + j));
		i++;
	}
	return (ft_strdup(""));
}

// 分割数と分割したトークンのvalueを格納
static void	remake_token(t_tokenlist *tokenlist, char **values, t_token *token,
		char *str)
{
	int	k;
	int	l;

	if (!values[0][0] || !values[2][0])
		token->count = 2;
	else
		token->count = 3;
	token->split_token = (t_token **)malloc(sizeof(t_token *) * token->count);
	if (!token->split_token)
		return (free(str), free_tokenlist(tokenlist, values, NULL, FAILED));
	k = 0;
	l = 0;
	while (k < 3)
	{
		if (values[k][0])
		{
			token->split_token[l] = (t_token *)malloc(sizeof(t_token));
			if (!token->split_token[l])
				return (free(str), free_tokenlist(tokenlist, values, NULL,
						FAILED));
			token->split_token[l]->value = values[k];
			token->split_token[l]->type = UNSIGNED;
			token->split_token[l]->split_token = NULL;
			l++;
		}
		k++;
	}
	free(values);
	token->type = TOK_SPLIT;
}

//"Hello$USER"のようなトークンを適切に分割する
void	split_token(t_tokenlist *tokenlist, char *str, t_token *token,
		int count)
{
	char	**values;
	char	*tmp;

	if (!str || !ft_strcmp(token->value, str))
		return (free(str));
	values = (char **)malloc(sizeof(char *) * 4);
	if (!values)
		return (free(str), free_tokenlist(tokenlist, NULL, NULL, FAILED));
	values[0] = get_new_pre_value(token->value, str, count);
	if (!values[0])
		return (free(str), free_tokenlist(tokenlist, values, NULL, FAILED));
	values[1] = ft_strdup(str);
	if (!values[1])
		return (free(str), free_tokenlist(tokenlist, values, NULL, FAILED));
	tmp = ft_strstr(token->value, str);
	if (*(tmp + ft_strlen(str)))
	{
		values[2] = get_new_post_value(token->value, str, count);
		if (!values[2])
			return (free(str), free_tokenlist(tokenlist, values, NULL, FAILED));
	}
	else
	{
		values[2] = ft_strdup("");
		if (!values[2])
			return (free(str), free_tokenlist(tokenlist, values, NULL, FAILED));
	}
	values[3] = NULL;
	remake_token(tokenlist, values, token, str);
}
