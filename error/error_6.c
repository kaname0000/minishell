/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 22:11:50 by okaname           #+#    #+#             */
/*   Updated: 2025/04/16 21:45:48 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../free/free.h"
#include "../libft/libft.h"
#include "error.h"

void	error_accese(char *file)
{
	ft_putstr_fd("bash: ", 2);
	perror(file);
	exit(1);
}

void	error_open(char *file)
{
	ft_putstr_fd("bash: ", 2);
	perror(file);
	exit(1);
}

void	error_close(void)
{
	perror("bash: close");
	exit(1);
}

void	error_fork(t_mini *mini, t_tokenset *tokenset, int *pid)
{
	int	i;
	int	status;

	i = 0;
	free_mini(mini);
	free_tokenset1(tokenset);
	if (pid != NULL)
	{
		while (pid[i] != -1)
		{
			waitpid(pid[i], &status, 0);
			i++;
		}
	}
	perror("bash: fork");
	exit(1);
}

void	error_malloc1(t_mini *mini, t_tokenset *tokenset)
{
	mini->cmd = NULL;
	free_mini(mini);
	free_tokenset1(tokenset);
	ft_putstr_fd("Error: Memory allocation failed\n", 2);
	exit(1);
}
