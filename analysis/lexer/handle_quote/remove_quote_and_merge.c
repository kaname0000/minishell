/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_and_merge.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:57:26 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/29 18:57:45 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

// e"ch"oのように前後とくっつけるべき場合に対応
void	remove_quote_and_merge_ex(t_tokenset *tokenset, int i)
{
	char	*temp;
	char	*new_value;

	temp = ft_strjoin(tokenset->token[i - 1]->value, tokenset->token[i
			+ 1]->value);
	if (!temp)
		free_tokenset(tokenset, FAILED);
	new_value = ft_strjoin(temp, tokenset->token[i + 3]->value);
	free(temp);
	if (!new_value)
		free_tokenset(tokenset, FAILED);
	free(tokenset->token[i - 1]->value);
	tokenset->token[i - 1]->value = new_value;
	remove_token(tokenset, i, 4);
	tokenset->count -= 4;
	i = 0;
	while (i < tokenset->count)
		tokenset->token[i++]->type = UNSIGNED;
}
