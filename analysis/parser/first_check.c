/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:38:06 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/03 20:45:37 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	first_check(t_tokenset *tokenset)
{
	if (tokenset->token[0]->type == TOK_PIPE)
	{
		write(2, "bash: syntax error near unexpected token `|'\n", 45);
		exit(2);
	}
}
