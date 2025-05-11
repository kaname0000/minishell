/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:54:52 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/11 20:16:00 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operators.h"

static char	*get_env_ex(t_mini *mini, char *env)
{
	char	*status;
	t_env	*temp;

	if (!ft_strcmp(env, "?"))
	{
		status = ft_itoa(mini->exit_status);
		if (!status)
			return (NULL);
		return (status);
	}
	temp = mini->var_env;
	while (temp->next)
	{
		if (!ft_strcmp(temp->key, env))
			return (ft_strdup((temp->value)));
		temp = temp->next;
	}
	return (ft_strdup(""));
}

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

static char	*reshape_input(char *input, int i, int e_len, char *value)
{
	int		v_len;
	char	*new;
	int		j;
	int		k;

	v_len = ft_strlen(value);
	new = (char *)malloc(sizeof(char) * (ft_strlen(input) - e_len + v_len));
	if (!new)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new[j] = input[j];
		j++;
	}
	k = 0;
	while (k < v_len)
		new[j++] = value[k++];
	while (j < (int)ft_strlen(input) - e_len + v_len - 1)
		new[j++] = input[i++ + e_len + 1];
	new[j] = '\0';
	return (new);
}

// inputの値を展開した状態に更新する
static char	*get_new_input(char *input, int i, int len, t_mini *mini)
{
	int		j;
	char	*env;
	char	*value;
	char	*new;

	if (!len)
		return (input);
	env = (char *)malloc(sizeof(char) * (len + 1));
	if (!env)
		return (NULL);
	j = 0;
	while (j < len)
	{
		env[j] = input[i + j + 1];
		j++;
	}
	env[j] = '\0';
	value = get_env_ex(mini, env);
	free(env);
	if (!value)
		return (NULL);
	new = reshape_input(input, i, len, value);
	free(value);
	return (new);
}

//環境変数や終了ステータスを展開し、inputを更新、その場合正の値を返す。
char	*expand_line(char *input, t_mini *mini)
{
	int		i;
	char	*new;

	i = 0;
	new = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			if (i == (int)ft_strlen(input) - 1)
				continue ;
			if (input[i + 1] == '?')
				new = get_new_input(input, i, 1, mini);
			else
				new = get_new_input(input, i, check_env_var(input, i + 1),
						mini);
			free(input);
			if (!new)
				exit(EXIT_FAILURE);
			input = new;
			i = 0;
		}
		i++;
	}
	return (input);
}
