/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 22:11:50 by okaname           #+#    #+#             */
/*   Updated: 2025/04/04 23:36:58 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

int	error_accese(char *file)
{
	ft_putstr_fd("bash: ", 2);
	perror(file);
	return (-1);
}

int	error_open(char *file)
{
	ft_putstr_fd("bash: ", 2);
	perror(file);
	return (-1);
}

int	error_close(void)
{
	perror("bash: close");
	return (-1);
}
