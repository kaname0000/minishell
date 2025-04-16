/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:59:57 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/16 17:23:36 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	syntax_analysis(t_tokenset *tokenset)
{
	int	i;

	i = 0;
	while (i < tokenset->count)
	{
		if (!check_pipe(tokenset, i))
			return (FAILED);
		if (!check_redirect(tokenset, i))
			return (FAILED);
		i++;
	}
	return (SUCCESS);
}
