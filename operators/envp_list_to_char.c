/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list_to_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 04:04:43 by okaname           #+#    #+#             */
/*   Updated: 2025/04/01 04:52:31 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operators.h"

static int	count_list(t_env *list)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = list;
	while (tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**list_to_char(t_env *env)
{
	char	**envp_char;
	int		count;
	int		i;
	t_env	*tmp;

	count = count_list(env);
	envp_char = malloc(sizeof(char *) * (count + 1));
	if (envp_char == NULL)
		error_malloc(NULL, NULL);
	envp_char[count] = NULL;
	i = 0;
	tmp = env;
	while (i < count)
	{
		envp_char[i] = ft_strjoin(tmp->key, "=");
		if (envp_char[i] == NULL)
			error_malloc(NULL, NULL);
		envp_char[i] = ft_strjoin_free(envp_char[i], tmp->value);
		if (envp_char[i] == NULL)
			error_malloc(NULL, NULL);
		tmp = tmp->next;
		i++;
	}
	return (envp_char);
}
