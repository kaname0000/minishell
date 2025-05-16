/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:36:08 by okaname           #+#    #+#             */
/*   Updated: 2025/05/12 19:04:35 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static int	ft_atoi_with_error(char *n, int *error_flag)
{
	int		i;
	long	num;
	int		sign;

	i = 0;
	num = 0;
	sign = 1;
	if ((n[i] == '+') || (n[i] == '-'))
	{
		if (n[i] == '-')
			sign = -sign;
		i++;
	}
	while (ft_isdigit(n[i]))
	{
		if ((sign == 1 && (num > (INT_MAX - (n[i] - '0')) / 10)) || (sign == -1
				&& (-num < (INT_MIN + (n[i] - '0')) / 10)))
			*error_flag = 1;
		num = num * 10 + (n[i++] - '0');
	}
	if (n[i] != '\0')
		*error_flag = 1;
	return ((int)num * sign);
}

static int	count_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		i++;
	}
	return (i);
}

static void	print1(char *str)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	ft_exit(t_mini *mini, int count)
{
	int	error_flag;
	int	status;

	error_flag = 0;
	if (mini->cmd[count]->cmd[1] == NULL)
	{
		printf("exit\n");
		return (free_tokenset(mini->tokenset, 1),
			free_array(mini->cmd[0]->envp), free_mini(mini), exit(0), 0);
	}
	status = ft_atoi_with_error(mini->cmd[count]->cmd[1], &error_flag);
	if (error_flag)
	{
		print1(mini->cmd[count]->cmd[1]);
		return (free_tokenset(mini->tokenset, 1),
			free_array(mini->cmd[0]->envp), free_mini(mini), exit(2), 0);
	}
	if (count_strs(mini->cmd[count]->cmd) > 2)
		return (ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2),
			1);
	printf("exit\n");
	return (free_tokenset(mini->tokenset, 1), free_array(mini->cmd[0]->envp),
		free_mini(mini), exit(status), 0);
}
