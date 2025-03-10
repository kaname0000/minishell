/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:01:29 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/10 23:27:18 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_tokentype.h"

// static char	*get_env_var(char *tmp, int i)
// {
// 	char	*env;
// 	int		j;

// 	env = (char *)malloc(sizeof(char) * i);
// 	if (!env)
// 		return (NULL);
// 	j = 0;
// 	while (j < i - 1)
// 	{
// 		env[j] = tmp[j + 1];
// 		j++;
// 	}
// 	env[j] = '\0';
// 	return (env);
// }

// int	check_env_var(t_token *token)
// {
// 	char	*tmp;
// 	int		i;
// 	char	*env;

// 	tmp = ft_strchr(token->value, '$');
// 	if (token->squote || !tmp)
// 		return (FAILED);
// 	if (!ft_isalpha(tmp[1]) && tmp[1] != '_')
// 		return (FAILED);
// 	i = 2;
// 	while (tmp[i])
// 	{
// 		if (!ft_isalnum(tmp[i]) && tmp[i] != '_')
// 			break ;
// 		i++;
// 	}
// 	env = get_env_var(tmp, i);
// 	if (!env || !getenv(env))
// 		return (free(env), FAILED);
// 	free(env);
// 	return (SUCCESS);
// }

int	check_env_var(t_token *token)
{
	int	i;

	i = 0;
	while (token->value[i] && token->value[i] != '$')
		i++;
	if (!token->value[i])
		return (FAILED);
}
