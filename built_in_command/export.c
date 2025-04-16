/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:46:29 by okaname           #+#    #+#             */
/*   Updated: 2025/04/16 21:54:07 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static void	append_env(t_env *env, char *s)
{
	int	i;
	int	equal_flag;
	int	plus_flag;

	i = 0;
	equal_flag = 0;
	plus_flag = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '+')
			equal_flag = 1;
		else if (s[i] == '=')
			equal_flag = 1;
	}
	(void)env;
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
				break ;
			append_env(mini->var_env, mini->cmd[count]->cmd[i]);
			i++;
		}
	return (0);
}
