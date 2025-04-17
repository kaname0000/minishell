/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_command_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:19:02 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/17 23:18:15 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

//対象が結合すべきであるか判別
static int	inspect_quote_edges(t_tokenset *tokenset, int i, int j)
{
	if (tokenset->token[i]->type == TOK_SQUOTE_START
		|| tokenset->token[i]->type == TOK_DQUOTE_START)
	{
		if (!j || tokenset->input[j - 1] == ' ')
			return (NO_JOIN);
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
static void	remove_token(t_tokenset *tokenset, int i)
{
	t_token	**new;
	int		j;
	int		k;

	new = (t_token **)malloc(sizeof(t_token *) * (tokenset->count - 3));
	if (!new)
		free_tokenset(tokenset, FAILED);
	j = 0;
	while (j < i)
	{
		new[j] = tokenset->token[j];
		j++;
	}
	k = 0;
	while (k < 3)
	{
		free(tokenset->token[i + k]->value);
		free(tokenset->token[i + k]);
		k++;
	}
	i += 3;
	while (j < tokenset->count - 3)
		new[j++] = tokenset->token[i++];
	free(tokenset->token);
	tokenset->token = new;
}

static int	is_builtin(char *value)
{
	if (!ft_strcmp(value, "echo") || !ft_strcmp(value, "cd")
		|| !ft_strcmp(value, "pwd") || !ft_strcmp(value, "export")
		|| !ft_strcmp(value, "unset") || !ft_strcmp(value, "env")
		|| !ft_strcmp(value, "exit"))
		return (SUCCESS);
	else
		return (FAILED);
}

// quoteのtokenを削除しつつ、前後どちらかと合体させる
static void	remove_quote_and_merge(t_tokenset *tokenset, int i, int key)
{
	char	*new_value;

	new_value = ft_strjoin(tokenset->token[i - 1]->value, tokenset->token[i
			+ 1]->value);
	printf("%s\n", tokenset->token[i + 1]->value);
	if (!new_value)
		free_tokenset(tokenset, FAILED);
	if (key == BACK)
		i += 2;
	free(tokenset->token[i - 1]->value);
	tokenset->token[i - 1]->value = new_value;
	if (key == BACK)
		i -= 4;
	remove_token(tokenset, i);
	tokenset->count -= 3;
	if (key == BACK)
		i++;
	if (is_builtin(tokenset->token[i - 1]->value))
		tokenset->token[i - 1]->type = TOK_BUILTIN;
	else
		tokenset->token[i - 1]->type = TOK_WORD;
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
				remove_quote_and_merge(tokenset, i, key);
				return (SUCCESS);
			}
		}
		i++;
	}
	return (FAILED);
}
