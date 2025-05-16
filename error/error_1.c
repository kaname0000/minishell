/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:37:54 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/12 20:21:11 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	error_arg(void)
{
	write(2, "Error: Invalid Arguments\n", 26);
	exit(1);
}

void	error_pipe(void)
{
	perror("minishell: pipe");
	exit(1);
}

void	error_infile_invalid(char *infile)
{
	write(2, "minishell: ", 11);
	perror(infile);
}

void	error_infile_open_failed(char *infile)
{
	write(2, "minishell: ", 11);
	perror(infile);
}

void	error_infile_close_failed(void)
{
	perror("minishell: close");
}
