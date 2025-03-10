/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamotoyota <okamotoyota@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:47:17 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/11 02:55:48 by okamotoyota      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_tokentype.h"

//$がvalue内に見つかるたびに呼び出され終了ステータスとして適切かチェック
static int	is_valid_exit_status(t_token *token, int i)
{
	if (token->squote[i] || (i && token->value[i - 1] == '\\'))
		return (FAILED);
	if (token->value[i + 1] != '?')
		return (FAILED);
	return (SUCCESS);
}

// 終了ステータスを示すTOK_EXIT_STATUSに該当するかチェック
int	check_exit_status(t_token *token)
{
	int	i;
	int	j;

	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '$')
		{
			if (is_valid_exit_status(token, i))
				return (SUCCESS);
		}
		i++;
	}
	return (FAILED);
}
