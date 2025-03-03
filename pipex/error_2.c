/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:49:29 by yookamot          #+#    #+#             */
/*   Updated: 2024/12/11 21:57:21 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_redirect(void)
{
	perror("bash");
	exit(1);
}

void	error_malloc(char **arr1, char **arr2)
{
	if (arr1)
	{
		ft_free_split(arr1);
		arr1 = NULL;
	}
	if (arr2)
	{
		ft_free_split(arr2);
		arr2 = NULL;
	}
	write(2, "Error: Memory allocation failed\n",
		ft_strlen("Error: Memory allocation failed\n"));
	exit(1);
}

void	error_command1(char **cmd_parts)
{
	write(2, cmd_parts[0], ft_strlen(cmd_parts[0]));
	write(2, ": command not found\n", 21);
	ft_free_split(cmd_parts);
	cmd_parts = NULL;
}

void	error_execve1(void)
{
	perror("bash");
}

void	error_fork1(void)
{
	perror("bash: fork");
}
