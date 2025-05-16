/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_space_between_symbol_and_quote.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:27:58 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/15 23:57:30 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

// symbolの個数を返す
static int	get_symbol_count(t_tokenset *tokenset, int i, char *value)
{
	int	j;
	int	k;
	int	l;
	int	count;

	j = 0;
	count = 1;
	while (j < i)
	{
		k = 0;
		while (tokenset->token[j]->value[k])
		{
			l = 0;
			while (value[l] && tokenset->token[j]->value[k + l]
				&& value[l] == tokenset->token[j]->value[k + l])
				l++;
			if (!value[l])
				count++;
			k++;
		}
		j++;
	}
	return (count);
}

static int	get_space_position(t_tokenset *tokenset, int i, int key)
{
	int	count;
	int	j;
	int	k;

	count = get_symbol_count(tokenset, i, tokenset->token[i]->value);
	j = 0;
	while (tokenset->input[j])
	{
		k = 0;
		while (tokenset->input[j + k] && tokenset->token[i]->value[k]
			&& tokenset->input[j + k] == tokenset->token[i]->value[k])
			k++;
		if (!tokenset->token[i]->value[k])
			count--;
		if (!count)
		{
			if (key == FRONT)
				return (j);
			else
				return (j + 1);
		}
		j++;
	}
	return (-1);
}

//実際にスペースを入れる
static void	insert_space_around_symbol(t_tokenset *tokenset, int i, int key)
{
	char	*new;
	int		j;
	int		p;

	p = get_space_position(tokenset, i, key);
	if (tokenset->input[p - 1] == ' ')
		return ;
	new = (char *)malloc(sizeof(char) * (ft_strlen(tokenset->input) + 2));
	if (!new)
		free_tokenset(tokenset, FAILED);
	j = 0;
	while (j < p)
	{
		new[j] = tokenset->input[j];
		j++;
	}
	new[j++] = ' ';
	while (tokenset->input[p])
		new[j++] = tokenset->input[p++];
	new[j] = '\0';
	free(tokenset->input);
	tokenset->input = new;
}

// echo <"test.txt"のような時、inputにリダイレクトとクオートの間にスペースを入れたい
void	insert_space_between_symbol_and_quote(t_tokenset *tokenset)
{
	int	i;
	int	pre_type;
	int	next_type;

	i = 0;
	while (i < tokenset->count)
	{
		if (tokenset->token[i]->type == TOK_PIPE
			|| tokenset->token[i]->type == TOK_REDIR_APPEND
			|| tokenset->token[i]->type == TOK_HEREDOC
			|| tokenset->token[i]->type == TOK_REDIR_IN
			|| tokenset->token[i]->type == TOK_REDIR_OUT)
		{
			pre_type = tokenset->token[i - 1]->type;
			next_type = tokenset->token[i + 1]->type;
			if (i && (pre_type == TOK_SQUOTE_END || pre_type == TOK_DQUOTE_END))
				insert_space_around_symbol(tokenset, i, FRONT);
			if (i < tokenset->count - 1 && (next_type == TOK_SQUOTE_START
					|| next_type == TOK_DQUOTE_START))
				insert_space_around_symbol(tokenset, i, BACK);
		}
		i++;
	}
}
