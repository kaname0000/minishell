/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:31:18 by okaname           #+#    #+#             */
/*   Updated: 2025/04/13 18:23:05 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../error/error.h"
#include "../free/free.h"
#include "../minishell.h"

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
	new_node->key = ft_strdup(tmp[0]);
	if (tmp[1] == NULL)
		new_node->value = ft_strdup("");
	else
		new_node->value = ft_strdup(tmp[1]);
	new_node->next = NULL;
	free_array(tmp);
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
		error_malloc(NULL, NULL);
	tmp = head;
	i = 1;
	while (env[i] != NULL)
	{
		new_node = make_node(env[i]);
		if (new_node == NULL)
			return (free_list(head), NULL);
		tmp->next = new_node;
		tmp = tmp->next;
		i++;
	}
	return (head);
}
