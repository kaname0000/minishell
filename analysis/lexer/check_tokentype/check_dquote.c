/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dquote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamotoyota <okamotoyota@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 03:25:14 by okamotoyota       #+#    #+#             */
/*   Updated: 2025/03/11 03:27:46 by okamotoyota      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_tokentype.h"

int	check_dquote(t_token *token)
{
	int	i;

	if (!token->value)
		return (FAILED);
	i = 0;
	while (token->value[i])
	{
		if (token->dquote[i])
			return (SUCCESS);
		i++;
	}
	return (FAILED);
}
