/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:47:17 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/13 14:33:32 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_tokentype.h"

//$がvalue内に見つかるたびに呼び出され終了ステータスとして適切かチェック
static int	is_valid_exit_status(t_token *token, int i)
{
	if (token->squote[i] || (i && token->value[i - 1] == '\\'))
		return (FAILED);
	return (SUCCESS);
}

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
			if (is_valid_exit_status(token, i))
				return (count);
		}
		i++;
	}
	return (FAILED);
}
