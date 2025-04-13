/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:47:17 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/05 01:34:14 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_tokentype.h"

// 終了ステータスを示すTOK_EXIT_STATUSに該当するかチェック
int	check_exit_status(t_token *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token->value[i])
	{
		if (token->value[i] == '$' && token->value[i + 1] == '?')
		{
			count++;
			if (!token->squote)
				return (count);
		}
		i++;
	}
	return (FAILED);
}
