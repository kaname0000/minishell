/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:46:29 by okaname           #+#    #+#             */
/*   Updated: 2025/05/01 15:45:28 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static t_env	*serch_key(t_env *env, char *s)
{
	t_env	*temp;

	temp = env;
	while (temp->next)
	{
		if (!ft_strcmp(temp->key, s))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	make_empty_value(t_env **env, char *s)
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

int	add_env_value(t_env **env, char *s)
{
	t_env	*tmp;
	t_env	*new_node;
	t_env	*last;

	last = *env;
	while (last->next)
		last = last->next;
	tmp = serch_key(*env, s);
	if (tmp != NULL)
	{
		tmp->value = ft_strjoin_free(tmp->value, ft_strchr(s, '=') + 1);
		if (tmp->value == NULL)
			return (1);
	}
	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
		return (1);
	last->next = new_node;
	new_node->key = ft_strndup_gnl(s, ft_strchr(s, '+') - s);
	new_node->value = ft_strdup(ft_strchr(s, '=') + 1);
	new_node->next = NULL;
	return (0);
}

int	ft_strdup_free(char **dst, char *s1, char *free_char)
{
	free(free_char);
	*dst = ft_strdup(s1);
	if (*dst == NULL)
		return (1);
	return (0);
}

static int	remake_env(t_env **env, char *s)
{
	t_env	*tmp;
	t_env	*new_node;
	t_env	*last;

	if (!ft_strchr(s, '='))
		return (make_empty_value(env, s));
	if (*(ft_strchr(s, '=') - 1) == '+')
		return (add_env_value(env, s));
	last = *env;
	while (last->next)
		last = last->next;
	tmp = serch_key(*env, s);
	if (tmp != NULL)
		return (ft_strdup_free(&tmp->value, ft_strchr(s, '=') + 1, tmp->value));
	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
		return (1);
	last->next = new_node;
	new_node->key = ft_strndup_gnl(s, ft_strchr(s, '=') - s);
	new_node->value = ft_strdup(ft_strchr(s, '=') + 1);
	new_node->next = NULL;
	return (0);
}

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
