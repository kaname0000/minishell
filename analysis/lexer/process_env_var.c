/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 00:52:47 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/10 16:31:09 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//環境変数が何文字あるかチェック、無効なら０
static int	check_env_var(char *input, int i)
{
	int	j;

	j = i;
	if (!ft_isalpha(input[i]) && input[i] != '_')
		return (FAILED);
	i++;
	while (input[i])
	{
		if (!ft_isalnum(input[i]) && input[i] != '_')
			break ;
		i++;
	}
	return (i - j);
}

static void	reshape_input(t_tokenlist *tokenlist, int i, int e_len, char *value)
{
	int		v_len;
	char	*new;
	int		j;
	int		k;

	v_len = ft_strlen(value);
	new = (char *)malloc(sizeof(char) * (ft_strlen(tokenlist->input) - e_len
				+ v_len));
	if (!new)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	j = 0;
	while (j < i)
	{
		new[j] = tokenlist->input[j];
		j++;
	}
	k = 0;
	while (k < v_len)
		new[j++] = value[k++];
	while (j < (int)ft_strlen(tokenlist->input) - e_len + v_len - 1)
		new[j++] = tokenlist->input[i++ + e_len + 1];
	new[j] = '\0';
	free(tokenlist->input);
	free(value);
	tokenlist->input = new;
}

// inputの値を展開した状態に更新する
static int	get_new_input(t_tokenlist *tokenlist, t_mini *mini, int i, int len)
{
	int		j;
	char	*env;
	char	*value;

	if (!len)
		return (FAILED);
	env = (char *)malloc(sizeof(char) * (len + 1));
	if (!env)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	j = 0;
	while (j < len)
	{
		env[j] = tokenlist->input[i + j + 1];
		j++;
	}
	env[j] = '\0';
	value = get_env(mini, env, tokenlist);
	free(env);
	if (!value)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	reshape_input(tokenlist, i, len, value);
	return (SUCCESS);
}

//環境変数や終了ステータスを展開し、inputを更新、その場合正の値を返す。
static int	expand_env_var(t_tokenlist *tokenlist, t_mini *mini)
{
	int	i;
	int	key;

	i = 0;
	key = 0;
	while (tokenlist->input[i])
	{
		if (tokenlist->input[i] == '$' && !tokenlist->sflag[i])
		{
			if (i == (int)ft_strlen(tokenlist->input) - 1)
				return (FAILED);
			if (tokenlist->input[i + 1] == '?')
				key = get_new_input(tokenlist, mini, i, 1);
			else
				key = get_new_input(tokenlist, mini, i,
						check_env_var(tokenlist->input, i + 1));
			if (key)
				return (SUCCESS);
		}
		i++;
	}
	return (FAILED);
}

void	process_env_var(t_tokenlist *tokenlist, t_mini *mini)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokenlist->input[i])
	{
		if (tokenlist->input[i] == '$')
			count++;
		i++;
	}
	if (!count)
		return ;
	i = ft_strlen(tokenlist->input);
	tokenlist->sflag = (int *)ft_calloc(sizeof(int), i);
	if (!tokenlist->sflag)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	tokenlist->dflag = (int *)ft_calloc(sizeof(int), i);
	if (!tokenlist->dflag)
		return (free_tokenlist(tokenlist, NULL, NULL, FAILED));
	while (make_quote_flag(tokenlist))
		;
	while (expand_env_var(tokenlist, mini))
		;
}
