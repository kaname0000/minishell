/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 05:44:39 by okaname           #+#    #+#             */
/*   Updated: 2025/05/24 00:54:41 by okaname          ###   ########.fr       */
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
			if (!array[j]->key || ft_strncmp(array[j]->key, array[j + 1]->key,
					INT_MAX) > 0)
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

void	print_env(t_env **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (array[i]->key == NULL)
		{
			i++;
			continue ;
		}
		if (array[i]->value)
			printf("declare -x %s=\"%s\"\n", array[i]->key, array[i]->value);
		else
			printf("declare -x %s\n", array[i]->key);
		i++;
	}
}

int	print_sorted_env(t_env *head)
{
	int		size;
	t_env	**array;
	t_env	*tmp;
	int		i;

	i = 0;
	size = list_size(head);
	if (size == 0)
		return (0);
	array = malloc(sizeof(t_env *) * size);
	if (!array)
		return (1);
	tmp = head;
	while (i < size)
	{
		array[i] = tmp;
		tmp = tmp->next;
		i++;
	}
	sort_array(array, size);
	print_env(array, size);
	free(array);
	return (0);
}

void	print_list(t_env *head)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->value != NULL)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
