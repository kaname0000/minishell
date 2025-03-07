/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:17:11 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/07 16:01:49 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//この中で無効な読み取り操作、"valgrind -s ./a.out"
static void	reshape_token(t_tokenlist *tokenlist, int i, int j)
{
	char	*tmp_value;
	char	*new_value;

	tmp_value = ft_strjoin(tokenlist->token[i][j - 1].value, " ");
	if (!tmp_value)
		free_tokenlist(tokenlist);
	new_value = ft_strjoin(tmp_value, tokenlist->token[i][j].value);
	printf("%s\n", new_value);
	free(tmp_value);
	if (!new_value)
		free_tokenlist(tokenlist);
	free(tokenlist->token[i][j - 1].value);
	free(tokenlist->token[i][j].value);
	tokenlist->token[i][j - 1].value = new_value;
	while (j < tokenlist->token_count[i])
	{
		tokenlist->token[i][j].value = tokenlist->token[i][j + 1].value;
		j++;
	}
	tokenlist->token_count[i]--;
}

static void	check(t_tokenlist *tokenlist, int c)
{
	int		i;
	int		j;
	char	*p_value;
	char	*c_value;

	i = 0;
	p_value = NULL;
	while (i < tokenlist->set_count)
	{
		j = 0;
		while (tokenlist->token[i][j].value)
		{
			c_value = tokenlist->token[i][j].value;
			if (p_value && p_value[0] == c && p_value[ft_strlen(p_value)
				- 1] != c)
			{
				printf("%s\n", p_value);
				printf("%s\n", c_value);
				if (c_value[0] != c && c_value[ft_strlen(c_value) - 1] == c)
				{
					reshape_token(tokenlist, i, j--);
				}
			}
			p_value = tokenlist->token[i][j].value;
			j++;
		}
		i++;
		p_value = NULL;
	}
}

//"Hello World"のような値がないかチェック
void	check_quote(t_tokenlist *tokenlist)
{
	check(tokenlist, '\'');
	check(tokenlist, '\"');
}
