/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:25:44 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/10 20:27:36 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

static void	free_iranai_token(t_tokenset *tokenset, int start, int end)
{
	int	j;

	j = start - 1;
	while (j <= end)
	{
		if (j != start)
		{
			free(tokenset->token[j]->value);
			free(tokenset->token[j]);
		}
		j++;
	}
	free(tokenset->token);
}

// new_valueをもとにtokensetを更新する
static void	reshape_tokenset(t_tokenset *tokenset, int start, int end)
{
	int		new_count;
	t_token	**new_arr;
	int		i;
	int		j;

	new_count = tokenset->count - end + start - 1;
	new_arr = (t_token **)malloc(sizeof(t_token *) * new_count);
	if (!new_arr)
		free_tokenset(tokenset, FAILED);
	i = 0;
	while (i < start - 1)
	{
		new_arr[i] = tokenset->token[i];
		i++;
	}
	new_arr[i++] = tokenset->token[start];
	j = end + 1;
	while (j < tokenset->count)
		new_arr[i++] = tokenset->token[j++];
	free_iranai_token(tokenset, start, end);
	tokenset->token = new_arr;
	tokenset->count = new_count;
}

// "hello world"に対応
int	join_token(t_tokenset *tokenset, int start, int end)
{
	int		a;
	int		b;
	char	*new_value;

	if (end - start == 2)
		return (FAILED);
	a = search_quote(tokenset, start);
	b = search_quote(tokenset, end);
	new_value = make_new_value(tokenset->input, a, b);
	if (!new_value)
		free_tokenset(tokenset, FAILED);
	start++;
	free(tokenset->token[start]->value);
	tokenset->token[start]->value = new_value;
	reshape_tokenset(tokenset, start, end);
	return (SUCCESS);
}
