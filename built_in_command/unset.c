/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 05:46:20 by okaname           #+#    #+#             */
/*   Updated: 2025/04/16 22:30:31 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static void	free_node(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

static void	delete_list(t_env **envp, char *key)
{
	t_env	*tmp1;
	t_env	*tmp2;

	tmp2 = NULL;
	tmp1 = *envp;
	while (tmp1)
	{
		if (!ft_strcmp(tmp1->key, key) && tmp2 == NULL)
		{
			*envp = tmp1->next;
			return (free_node(tmp1));
		}
		else if (!ft_strcmp(tmp1->key, key))
		{
			tmp2->next = tmp1->next;
			return (free_node(tmp1));
		}
		tmp2 = tmp1;
		tmp1 = tmp1->next;
	}
}

int	ft_unset(t_mini *mini, int count)
{
	int	i;

	i = 1;
	while (mini->cmd[count]->cmd[i] != NULL)
	{
		delete_list(&(mini->var_env), mini->cmd[count]->cmd[i]);
		i++;
	}
	return (0);
}
