/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 05:44:39 by okaname           #+#    #+#             */
/*   Updated: 2025/03/26 01:16:32 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static int	list_size(t_env *head)
{
	int	size;

	size = 0;
	while (head)
	{
		size++;
		head = head->next;
	}
	return (size);
}

static void	sort_array(t_env **array, int size)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (ft_strncmp(array[j]->key, array[j + 1]->key, INT_MAX) > 0)
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_sorted_env(t_env *head)
{
	int		size;
	t_env	**array;
	t_env	*tmp;
	int		i;

	i = 0;
	size = list_size(head);
	if (size == 0)
		return ;
	array = malloc(sizeof(t_env *) * size);
	if (!array)
		return ;
	tmp = head;
	while (i < size)
	{
		array[i] = tmp;
		tmp = tmp->next;
		i++;
	}
	sort_array(array, size);
	i = -1;
	while (++i < size)
		printf("declare -x %s=\"%s\"\n", array[i]->key, array[i]->value);
	free(array);
}

void	print_list(t_env *head)
{
	while (head)
	{
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}
