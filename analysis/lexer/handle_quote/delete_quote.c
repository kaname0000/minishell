/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:17:57 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/08 19:57:48 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

// quoteの中身がbuiltinだったときにtype更新
static void	is_builtin(t_token *token)
{
	if (!ft_strcmp(token->value, "echo") || !ft_strcmp(token->value, "cd")
		|| !ft_strcmp(token->value, "pwd") || !ft_strcmp(token->value, "export")
		|| !ft_strcmp(token->value, "unset") || !ft_strcmp(token->value, "env")
		|| !ft_strcmp(token->value, "exit"))
		token->type = TOK_BUILTIN;
}

// quoteを削除したtokensetを作る
static void	delete_quote_token(t_tokenset *tokenset, int i)
{
	t_token	**new;
	int		j;

	tokenset->count -= 2;
	new = (t_token **)malloc(sizeof(t_token *) * tokenset->count);
	if (!new)
		free_tokenset(tokenset, FAILED);
	j = 0;
	while (j < i)
	{
		new[j] = tokenset->token[j];
		j++;
	}
	new[j] = tokenset->token[i + 1];
	is_builtin(new[j]);
	free(tokenset->token[i]->value);
	free(tokenset->token[i]);
	free(tokenset->token[i + 2]->value);
	free(tokenset->token[i + 2]);
	i += 3;
	j++;
	while (j < tokenset->count)
		new[j++] = tokenset->token[i++];
	free(tokenset->token);
	tokenset->token = new;
}

//空文字列をvalueにもつtoken生成
static t_token	*make_empty_token(t_tokenset *tokenset, int i)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		free_tokenset(tokenset, FAILED);
	new->value = ft_strdup("");
	if (!new->value)
		free_tokenset(tokenset, FAILED);
	if (tokenset->token[i]->type == TOK_SQUOTE_START)
		new->type = TOK_SQUOTE_IN;
	else
		new->type = TOK_DQUOTE_IN;
	return (new);
}

// ""のようにquoteの中身が何もないとき
static void	delete_quote_token_ex(t_tokenset *tokenset, int i)
{
	t_token	**new;
	int		j;

	tokenset->count--;
	new = (t_token **)malloc(sizeof(t_token *) * tokenset->count);
	if (!new)
		free_tokenset(tokenset, FAILED);
	j = 0;
	while (j < i)
	{
		new[j] = tokenset->token[j];
		j++;
	}
	new[j] = make_empty_token(tokenset, i);
	free(tokenset->token[i]->value);
	free(tokenset->token[i]);
	free(tokenset->token[i + 1]->value);
	free(tokenset->token[i + 1]);
	i += 2;
	while (j < tokenset->count)
		new[j++] = tokenset->token[i++];
	free(tokenset->token);
	tokenset->token = new;
}

// quoteを削除する
int	delete_quotes(t_tokenset *tokenset)
{
	int	i;

	i = 0;
	while (i < tokenset->count)
	{
		if (tokenset->token[i]->type == TOK_SQUOTE_START
			|| tokenset->token[i]->type == TOK_DQUOTE_START)
		{
			if (tokenset->token[i + 1]->type == TOK_SQUOTE_IN
				|| tokenset->token[i + 1]->type == TOK_DQUOTE_IN)
				delete_quote_token(tokenset, i);
			else
				delete_quote_token_ex(tokenset, i);
			return (SUCCESS);
		}
		i++;
	}
	return (FAILED);
}
