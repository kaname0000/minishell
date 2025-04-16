/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokentype.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:02:03 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/10 23:48:51 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
			if (!token->squote && i && token->value[i - 1] == '$')
				return (count);
		}
		i++;
	}
	return (FAILED);
}

static void	search_keyword2(t_token *token, t_tokenlist *tokenlist)
{
	if (check_double_symbol(token, "<<", tokenlist))
		return ;
	if (check_double_symbol(token, ">>", tokenlist))
		return ;
	if (check_redirection_out(token, tokenlist))
		return ;
	if (check_redirection_in(token, tokenlist))
		return ;
	if (check_squote(token, tokenlist))
		return ;
	if (check_dquote(token, tokenlist))
		return ;
}

// tokenのvalueの中から、キーワードを探し、見つけた場合はsplitする
static void	search_keyword(t_token *token, t_tokenlist *tokenlist, t_mini *mini)
{
	char	*env;
	int		count;

	env = check_env_var(token, tokenlist, mini);
	if (env)
	{
		count = count_env(token, env);
		if (count)
			return (split_token(tokenlist, env, token, count));
		free(env);
	}
	count = check_exit_status(token);
	if (count)
		return (split_token(tokenlist, ft_strdup("$?"), token, count));
	if (check_single_symbol(token, '|', tokenlist))
		return ;
	search_keyword2(token, tokenlist);
}

// token_typeの割当
void	check_tokentype(t_token *token, t_tokenlist *tokenlist, t_mini *mini)
{
	int	i;

	if (!token || !token->value)
		return ;
	search_keyword(token, tokenlist, mini);
	if (token->count > 1 && token->split_token)
	{
		i = 0;
		while (i < token->count)
		{
			if (token->split_token[i]->value)
				check_tokentype(token->split_token[i], tokenlist, mini);
			i++;
		}
	}
}
