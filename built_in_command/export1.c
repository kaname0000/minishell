/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:46:29 by okaname           #+#    #+#             */
/*   Updated: 2025/05/04 18:16:53 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static int	print_invalid(char *s)
{
	ft_putstr_fd(("bash: export: `"), 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd((": not a valid identifier\n"), 2);
	return (1);
}

static int	is_invalid(char *s)
{
	if (s[0] == '=' || s[0] == '+')
		return (print_invalid(s));
	if (!ft_strchr(s, '+') && !(ft_strchr(s, '-')))
		return (0);
	if (!ft_strchr(s, '=') && (ft_strchr(s, '-') || ft_strchr(s, '+')))
		return (print_invalid(s));
	if ((ft_strchr(s, '-') && ft_strchr(s, '=') - ft_strchr(s, '-') > 0)
		|| ((ft_strchr(s, '+') && ft_strchr(s, '=') - ft_strchr(s, '+') > 1)))
		return (print_invalid(s));
	return (0);
}

int	ft_export(t_mini *mini, int count)
{
	int	count_a;
	int	i;

	i = 1;
	count_a = count_array(mini->cmd[count]->cmd);
	if (count_a == 1)
	{
		if (print_sorted_env(mini->var_env))
			error_malloc1(mini, NULL);
	}
	else
	{
		while (mini->cmd[count]->cmd[i] != NULL)
		{
			if (is_invalid(mini->cmd[count]->cmd[i]))
				return (1);
			remake_env(&(mini->var_env), mini->cmd[count]->cmd[i]);
			i++;
		}
	}
	return (0);
}
