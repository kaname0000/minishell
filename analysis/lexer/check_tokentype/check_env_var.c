/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamotoyota <okamotoyota@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:01:29 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/17 09:59:18 by okamotoyota      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_tokentype.h"

// 環境変数の文字として適切かチェック
static int	check_literal(t_token *token, int i)
{
	if ((!ft_isalpha(token->value[i]) && token->value[i] != '_')
		|| token->squote)
		return (FAILED);
	return (SUCCESS);
}

//$VARのVARの部分を取得
static char	*get_env_var(char *value, int start, int end,
		t_tokenlist *tokenlist)
{
	char	*env;
	int		i;

	env = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!env)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	i = 0;
	while (i < end - start)
	{
		env[i] = value[start + i];
		i++;
	}
	env[i] = '\0';
	return (env);
}

//${VAR}のような形に対応
static char	*is_valid_env_name_brace(t_token *token, t_tokenlist *tokenlist,
		int i)
{
	int		j;
	char	*env;

	j = i;
	if (!check_literal(token, i))
		return (NULL);
	i++;
	while (token->value[i] && token->value[i] != '}')
	{
		if (!check_literal(token, i) || !ft_isdigit(token->value[i]))
			return (NULL);
		i++;
	}
	if (!token->value[i])
		return (NULL);
	env = get_env_var(token->value, j, i, tokenlist);
	if (!getenv(env))
		return (free(env), NULL);
	return (env);
}

//$がvalue内に見つかるたびに呼び出され環境変数として適切かチェック
static char	*is_valid_env_name(t_token *token, t_tokenlist *tokenlist, int i)
{
	int		j;
	char	*env;

	if (!token->value[i] || (i && token->value[i - 1] == '\\'))
		return (NULL);
	if (i && token->value[i - 1] == '\\')
	{
		if (i > 1 && token->value[i - 2] != '\\')
			return (NULL);
		if (i == 1)
			return (NULL);
	}
	i++;
	if (token->value[i] == '{')
		return (is_valid_env_name_brace(token, tokenlist, i + 1));
	j = i;
	if (!check_literal(token, i))
		return (NULL);
	i++;
	while (token->value[i])
	{
		if (!check_literal(token, i) && !ft_isdigit(token->value[i]))
			break ;
		i++;
	}
	env = get_env_var(token->value, j, i, tokenlist);
	if (!getenv(env))
		return (free(env), NULL);
	return (env);
}

// 環境変数を示すTOK_ENV_VARに該当する単語が存在するかのチェック
char	*check_env_var(t_token *token, t_tokenlist *tokenlist)
{
	int		i;
	char	*env;

	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '$')
		{
			env = is_valid_env_name(token, tokenlist, i);
			if (env)
				return (env);
		}
		i++;
	}
	return (NULL);
}
