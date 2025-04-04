/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_hundle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:55:26 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/03 22:40:49 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	error_token(t_tokenset *tokenset, char *value)
{
	if (value)
	{
		write(2, "minishell: syntax error: unexpected token `", 43);
		write(2, value, ft_strlen(value));
		write(2, "'\n", 2);
	}
	free_tokenset(tokenset);
	exit(2);
}

void	error_end_of_file(t_tokenset *tokenset, char *value)
{
	write(2, "minishell: syntax error: unexpected end of file (unclosed ", 58);
	if (value)
	{
		write(2, value, ft_strlen(value));
		write(2, " ", 1);
	}
	write(2, "quote)\n", 8);
	free_tokenset(tokenset);
	exit(EXIT_FAILURE);
}

void	error_outfile_invalid(t_tokenset *tokenset, char *file)
{
	write(2, "minishell: ", 11);
	perror(file);
	free_tokenset(tokenset);
	exit(EXIT_FAILURE);
}
