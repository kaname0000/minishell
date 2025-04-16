/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:46:29 by okaname           #+#    #+#             */
/*   Updated: 2025/04/16 23:49:14 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static char	*serch_key(t_env *env, char *s)
{
	t_env	*temp;

	temp = env;
	while (temp->next)
	{
		if (!ft_strcmp(temp->key, s))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

static void	append_env(t_env *env, char *s)
{
	// if (ft_strchr(s, '=') == NULL)
	// 	make_env(&env, s);
	// else if (ft_strchr(s, '=') == NULL)
	// 	make_node();
	serch_key(env, s);
}

static int	is_invalid(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '=' && i == 0)
		{
			ft_putstr_fd(("bash: export: `"), 2);
			ft_putstr_fd(s, 2);
			ft_putstr_fd((": not a valid identifier"), 2);
			return (0);
		}
		else if (s[i] == '-')
		{
			ft_putstr_fd(("bash: export: `"), 2);
			ft_putstr_fd(s, 2);
			ft_putstr_fd((": not a valid identifier"), 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_export(t_mini *mini, int count)
{
	int	count_a;
	int	i;

	i = 0;
	count_a = count_array(mini->cmd[count]->cmd);
	if (count_a == 1)
		print_sorted_env(mini->var_env);
	else
		while (mini->cmd[count]->cmd[i] != NULL)
		{
			if (is_invalid(mini->cmd[count]->cmd[i]))
				return (1);
			append_env(mini->var_env, mini->cmd[count]->cmd[i]);
			i++;
		}
	return (0);
}
