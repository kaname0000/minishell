/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:18:34 by okaname           #+#    #+#             */
/*   Updated: 2025/04/08 21:53:47 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	count_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

static char	*get_home_path(t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "HOME", 4))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_cd(t_mini *mini, int count)
{
	int		count_a;
	char	*home_path;

	count_a = count_array(mini->cmd[count]->cmd);
	if (count_a > 2)
		return (ft_putstr_fd("bash: cd: too many arguments\n", 2), 1);
	else if (count_a == 1)
	{
		home_path = get_home_path(mini->var_env);
		if (home_path == NULL)
			return (ft_putstr_fd("bash: cd: HOME not set\n", 2), 1);
		else if (chdir(home_path) == -1)
			return (perror("chdir failed"), 1);
	}
	else if (chdir(mini->cmd[count]->cmd[1]) == -1)
		return (perror("chdir failed"), 1);
	return (ft_pwd(mini, 0));
}
