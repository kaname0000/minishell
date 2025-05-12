/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_and_merge.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:57:26 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/12 21:33:16 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

// e"ch"o のような BOTH ケース
void	remove_quote_and_merge_ex(t_tokenset *tokenset, int open)
{
	char	*tmp;
	char	*new_value;
	int		k;

	tmp = ft_strjoin(tokenset->token[open - 1]->value, tokenset->token[open
			+ 1]->value);
	if (!tmp)
		free_tokenset(tokenset, FAILED);
	new_value = ft_strjoin(tmp, tokenset->token[open + 3]->value);
	free(tmp);
	if (!new_value)
		free_tokenset(tokenset, FAILED);
	free(tokenset->token[open - 1]->value);
	tokenset->token[open - 1]->value = new_value;
	remove_token(tokenset, open, 4);
	k = 0;
	while (k < tokenset->count)
		tokenset->token[k++]->type = UNSIGNED;
}
