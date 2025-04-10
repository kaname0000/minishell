/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 22:38:03 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/04 23:36:00 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// 環境変数の文字として適切かチェック
static int	check_literal(char *value, int i)
{
	if (!ft_isalpha(value[i]) && value[i] != '_')
		return (FAILED);
	return (SUCCESS);
}

//$VARのVARの部分を取得
static char	*get_env_var(char *value, int start, int end)
{
	char	*env;
	int		i;

	env = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!env)
	{
		free(value);
		value = NULL;
		return (NULL);
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

static char	*return_env_var(char *value, int i)
{
	char	*env;
	int		j;

	j = i;
	if (!check_literal(value, i))
		return (NULL);
	i++;
	while (token->value[i])
	{
		if (!check_literal(value, i) && !ft_isdigit(value[i]))
			break ;
		i++;
	}
	env = get_env_var(value, j, i);
	if (!env || !getenv(env))
		return (free(env), NULL);
	return (env);
}

static char	*remake_value(char *value, char *env, int i)
{
	int		count;
	char	*new;
	int		j;
	int		k;

	count = 1;
	while (check_literal(value, i + count) || ft_isdigit(value[i + count]))
		count++;
	new = (char *)malloc(sizeof(char) * (ft_strlen(value) + ft_strlen(env)
				- count + 1));
	if (!new)
		return (free(env), free(value), NULL);
	j = 0;
	k = 0;
	while (j < ft_strlen(value) + ft_strlen(env) - count)
	{
		if (j == i - 1)
		{
			i = 0;
			while (env[i])
				new[j++] = env[i++];
			k += count + 1;
		}
		new[j++] = value[k++];
	}
	new[j] = '\0';
	return (free(env), free(value), new);
}

char	*expand_env_var(char *new_value)
{
	int		i;
	char	*env;

	i = 0;
	while (new_value[i])
	{
		if (new_value[i] == '$')
		{
			env = return_env_var(new_value, i + 1);
			if (!new_value)
				return (NULL);
			if (!env)
				break ;
			new_value = remake_value(new_value, env, i + 1);
			if (!new_value)
				return (NULL);
			i = 0;
		}
		i++;
	}
}
