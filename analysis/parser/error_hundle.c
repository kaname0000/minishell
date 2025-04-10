/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_hundle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:55:26 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/08 21:52:51 by yookamot         ###   ########.fr       */
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
	free_tokenset(tokenset, SUCCESS);
}
