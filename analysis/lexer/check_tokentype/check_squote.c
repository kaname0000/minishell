/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_squote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamotoyota <okamotoyota@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 03:25:14 by okamotoyota       #+#    #+#             */
/*   Updated: 2025/03/11 03:30:32 by okamotoyota      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_tokentype.h"

// 現在の実装ではシングルとダブルが混在する場合の判定が曖昧なので、要確認
int	check_squote(t_token *token)
{
	int	i;

	if (!token->value)
		return (FAILED);
	i = 0;
	while (token->value[i])
	{
		if (token->squote[i])
			return (SUCCESS);
		i++;
	}
	return (FAILED);
}
