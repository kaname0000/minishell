/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:31:18 by okaname           #+#    #+#             */
/*   Updated: 2025/03/20 05:39:10 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	malloc_error(void)
{
	ft_putendl_fd("malloc error", STDERR_FILENO);
	exit(1);
}

void	free_list(t_env *head)
{
	t_env	*tmp;

	while (head != NULL)
	{
		tmp = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = tmp;
	}
	malloc_error();
}

static t_env	*make_node(char *str)
{
	t_env	*new_node;
	char	**tmp;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
		return (NULL);
	tmp = ft_split(str, '=');
	if (tmp == NULL)
		return (free(new_node), NULL);
	new_node->key = tmp[0];
	new_node->value = tmp[1];
	new_node->next = NULL;
	return (new_node);
}

t_env	*env_init(char **env)
{
	t_env	*head;
	t_env	*tmp;
	t_env	*new_node;
	int		i;

	head = make_node(env[0]);
	if (head == NULL)
		malloc_error();
	tmp = head;
	i = 1;
	while (env[i] != NULL)
	{
		new_node = make_node(env[i]);
		if (new_node == NULL)
			free_list(head);
		tmp->next = new_node;
		tmp = tmp->next;
		i++;
	}
	return (head);
}
