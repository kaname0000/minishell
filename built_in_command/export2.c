/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:27:02 by okaname           #+#    #+#             */
/*   Updated: 2025/05/04 18:53:40 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static t_env	*serch_key(t_env *env, char *s)
{
	t_env	*temp;
	char	*tmp;

	if (!ft_strchr(s, '='))
		tmp = ft_strdup(s);
	else if (*(ft_strchr(s, '=') - 1) == '+')
		tmp = ft_strndup_gnl(s, ft_strchr(s, '=') - s - 1);
	else
		tmp = ft_strndup_gnl(s, ft_strchr(s, '=') - s);
	temp = env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, tmp))
			return (free(tmp), temp);
		temp = temp->next;
	}
	free(tmp);
	return (NULL);
}

static int	make_empty_value(t_env **env, char *s)
{
	t_env	*tmp;
	t_env	*new_node;
	t_env	*last;

	tmp = serch_key(*env, s);
	if (tmp != NULL)
		return (0);
	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
		return (1);
	new_node->key = ft_strdup(s);
	new_node->value = NULL;
	new_node->next = NULL;
	last = *env;
	while (last->next)
		last = last->next;
	last->next = new_node;
	return (0);
}

static int	add_env_value(t_env **env, char *s)
{
	t_env	*tmp;
	t_env	*new_node;
	t_env	*last;

	tmp = serch_key(*env, s);
	if (tmp != NULL)
	{
		tmp->value = ft_strjoin_free(tmp->value, ft_strchr(s, '=') + 1);
		if (tmp->value == NULL)
			return (1);
		return (0);
	}
	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
		return (1);
	new_node->key = ft_strndup_gnl(s, ft_strchr(s, '+') - s);
	new_node->value = ft_strdup(ft_strchr(s, '=') + 1);
	new_node->next = NULL;
	last = *env;
	while (last->next)
		last = last->next;
	last->next = new_node;
	return (0);
}

static int	ft_strdup_free(char **dst, char *s1, char *free_char)
{
	free(free_char);
	*dst = ft_strdup(s1);
	if (*dst == NULL)
		return (1);
	return (0);
}

int	remake_env(t_env **env, char *s)
{
	t_env	*tmp;
	t_env	*new_node;
	t_env	*last;

	if (!ft_strchr(s, '='))
		return (make_empty_value(env, s));
	if (*(ft_strchr(s, '=') - 1) == '+')
		return (add_env_value(env, s));
	tmp = serch_key(*env, s);
	if (tmp != NULL)
		return (ft_strdup_free(&tmp->value, ft_strchr(s, '=') + 1, tmp->value));
	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
		return (1);
	new_node->key = ft_strndup_gnl(s, ft_strchr(s, '=') - s);
	new_node->value = ft_strdup(ft_strchr(s, '=') + 1);
	new_node->next = NULL;
	last = *env;
	while (last->next)
		last = last->next;
	last->next = new_node;
	return (0);
}
