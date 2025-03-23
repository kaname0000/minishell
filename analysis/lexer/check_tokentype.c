/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokentype.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamotoyota <okamotoyota@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:02:03 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/17 09:53:50 by okamotoyota      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// envと一致する文字列が環境変数として有効なものかチェック
static int	check_valid_env(t_token *token, int i, int len)
{
	int	value_len;

	if (token->squote)
		return (FAILED);
	value_len = ft_strlen(token->value);
	if (i && token->value[i - 1] == '{')
	{
		if (value_len > i + len && token->value[i + len] != '}')
			return (FAILED);
		i--;
	}
	if (i == 1 && token->value[i - 1] == '$')
		return (SUCCESS);
	if (i == 2 && token->value[i - 1] == '$' && token->value[i - 2] != '\\')
		return (SUCCESS);
	if (i > 2 && token->value[i - 1] == '$')
	{
		if (token->value[i - 2] != '\\')
			return (SUCCESS);
		else if (token->value[i - 3] == '\\')
			return (SUCCESS);
		else
			return (FAILED);
	}
	return (FAILED);
}

// 何個目のenvと一致する文字列を使うべきかを返す
static int	count_env(t_token *token, char *env)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (token->value[i])
	{
		j = 0;
		while (token->value[i + j] == env[j] && env[j])
			j++;
		if (!env[j])
		{
			count++;
			if (check_valid_env(token, i, ft_strlen(env)))
				return (count);
		}
		i++;
	}
	return (FAILED);
}

static void	search_keyword2(t_token *token, t_tokenlist *tokenlist)
{
	if (check_redirection(token, '>', tokenlist))
		return ;
	if (check_redirection(token, '<', tokenlist))
		return ;
	if (check_backslash(token, tokenlist))
		return ;
	if (check_double_symbol(token, ">>", tokenlist))
		return ;
	if (check_double_symbol(token, "<<", tokenlist))
		return ;
	if (check_squote(token, tokenlist))
		return ;
	if (check_dquote(token, tokenlist))
		return ;
	if (check_assignment(token, tokenlist))
		return ;
}

// tokenのvalueの中から、キーワードを探し、見つけた場合はsplitする
static void	search_keyword(t_token *token, t_tokenlist *tokenlist)
{
	char	*env;
	int		count;

	env = check_env_var(token, tokenlist);
	if (env)
	{
		count = count_env(token, env);
		if (count)
			return (split_token(tokenlist, env, token, count), free(env));
	}
	count = check_exit_status(token);
	if (count)
		return (split_token(tokenlist, ft_strdup("$?"), token, count));
	if (check_single_symbol(token, ';', tokenlist))
		return ;
	if (check_single_symbol(token, '&', tokenlist))
		return ;
	if (check_single_symbol(token, '|', tokenlist))
		return ;
	if (check_single_symbol(token, '{', tokenlist))
		return ;
	if (check_single_symbol(token, '}', tokenlist))
		return ;
	search_keyword2(token, tokenlist);
}

// token_typeの割当
void	check_tokentype(t_token *token, t_tokenlist *tokenlist)
{
	int	i;

	if (!token || !token->value)
		return ;
	token->count = 1;
	token->type = -1;
	search_keyword(token, tokenlist);
	if (token->count > 1 && token->split_token)
	{
		i = 0;
		while (i < token->count)
		{
			if (token->split_token[i]->value)
				check_tokentype(token->split_token[i], tokenlist);
			i++;
		}
	}
}
