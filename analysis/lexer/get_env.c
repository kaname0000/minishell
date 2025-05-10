/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:43:57 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/10 16:30:09 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*get_env(t_mini *mini, char *env, t_tokenlist *tokenlist)
{
	char	*status;
	t_env	*temp;

	if (!ft_strcmp(env, "?"))
	{
		status = ft_itoa(mini->exit_status);
		if (!status)
			free_tokenlist(tokenlist, NULL, NULL, FAILED);
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
