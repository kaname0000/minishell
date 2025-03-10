/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamotoyota <okamotoyota@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:01:29 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/11 02:45:19 by okamotoyota      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_tokentype.h"

// 環境変数の文字として適切かチェック
static int	check_literal(t_token *token, int i)
{
	if (!ft_isalpha(token->value[i]) || token->value[i] != '_'
		|| token->squote[i])
		return (FAILED);
	return (SUCCESS);
}

//$VARのVARの部分を取得
static char	*get_env_var(char *value, int start, int end,
		t_tokenlist *tokenlist)
{
	char	*env;
	int		i;

	env = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!env)
	{
		free_flag_array(tokenlist);
		free_tokenlist(tokenlist);
	}
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
static int	is_valid_env_name_brace(t_token *token, t_tokenlist *tokenlist,
		int i)
{
	int		j;
	char	*env;

	j = i;
	while (token->value[i] && token->value[i] != '}')
	{
		if (!check_literal(token, i))
			return (FAILED);
		i++;
	}
	if (!token->value[i])
		return (FAILED);
	env = get_env_var(token->value, j, i, tokenlist);
	if (!getenv(env))
		return (free(env), FAILED);
	return (free(env), SUCCESS);
}

//$がvalue内に見つかるたびに呼び出され環境変数として適切かチェック
static int	is_valid_env_name(void)
{
	if (!token->value[i] || (i && token->value[i - 1] == '\\'))
		return (FAILED);
	i++;
	if (token->value[i] == '{')
		return (is_valid_env_name_brace(token, tokenlist, i + 1));
	if (!check_literal(token, i))
		return (FAILED);
	j = i;
	while (token->value[i])
	{
		if (!check_literal(token, i))
			break ;
		i++;
	}
	env = get_env_var(token->value, j, i, tokenlist);
	if (!getenv(env))
		return (free(env), FAILED);
	return (free(env), SUCCESS);
}

// 環境変数を示すTOK_ENV_VARに該当するかのチェック
int	check_env_var(t_token *token, t_tokenlist *tokenlist)
{
	int		i;
	int		j;
	char	*env;

	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '$')
		{
			if (is_valid_env_name(token, tokenlist, i))
				return (SUCCESS);
		}
		i++;
	}
	return (FAILED);
}
