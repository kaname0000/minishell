/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_with_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 01:04:27 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/26 01:04:28 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

// "hello    world"のように複数のスペースがクオート配下にあるパターンに対応
void	tokenize_with_quotes(char *input, t_tokenset *tokenset)
{
	t_tokenset	*temp;
	int			i;
	int			count;

	temp = tokenset;
	i = 0;
	count = 0;
	while (i < tokenset->count)
	{
		if (tokenset->token[i]->type == TOK_DQUOTE_IN
			|| tokenset->token[i]->type == TOK_SQUOTE_IN)
		{
			count = search_str_in_token(tokenset, tokenset->token[i]->value, i);
		}
	}
}
