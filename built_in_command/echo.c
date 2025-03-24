/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:46:28 by okaname           #+#    #+#             */
/*   Updated: 2025/03/24 20:54:58 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	printf_var(char *str)
{
	return (printf("%s", str));
}

int	printf_str(char *str)
{
	int	i;
	int	flag;
	int	count;

	i = 0;
	flag = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\')
			flag++;
		if (flag ^ 1)
		{
			flag = 0;
			i++;
			continue ;
		}
		if (write(1, &str[i], 1) == -1)
			return (-1);
		i++;
		count++;
	}
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

int	echo(int nflag, char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		if (is_valid$(strs[i]))
			printf_var(strs[i]);
		else
			printf_str(strs[i]);
		i++;
	}
	if (!nflag)
		printf("\n");
	return (0);
}
