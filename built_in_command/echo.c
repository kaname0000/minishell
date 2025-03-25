/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:46:28 by okaname           #+#    #+#             */
/*   Updated: 2025/03/25 18:30:57 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	print_var(char *str, t_env *env)
{
	t_env	*tmp;
	int		len;

	tmp = env;
	len = ft_strlen(str);
	while (tmp != NULL)
	{
		if (ft_strncmp(str, tmp->key, len) == 0)
			return (printf("%s\n", tmp->value));
		tmp = tmp->next;
	}
	return (printf("\n"));
}

int	print_str(char *str)
{
	int		i;
	bool	flag;
	int		count;

	i = 0;
	flag = false;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\')
			flag = true;
		if (flag)
		{
			flag = false;
			i++;
			continue ;
		}
		if (write(1, &str[i], 1) == -1)
			return (-1);
		i++;
		count++;
	}
	write(1, "\n", 1);
	return (count);
}

int is_valid$(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\\')
		i++;
	if ((i ^ 1) && (str[i] == '$'))
		return (1);
	return (0);
}

int	ft_echo(int nflag, char **strs, t_env *env)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		if (is_valid$(strs[i]))
			print_var(&(strs[i][1]), env);
		else
			print_str(strs[i]);
		i++;
	}
	if (!nflag)
		printf("\n");
	return (0);
}
