/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 22:11:50 by okaname           #+#    #+#             */
/*   Updated: 2025/04/06 16:50:58 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
