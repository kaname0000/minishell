/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_daller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:00:35 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/11 22:35:52 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	search_daller(t_tokenset *tokenset)
{
	int		i;
	char	*new;

	i = 0;
	while (i < tokenset->count)
	{
		if (tokenset->token[i]->type == TOK_WORD
			&& tokenset->token[i]->value[0] == '$'
			&& tokenset->token[i]->value[1])
		{
			new = (char *)malloc(sizeof(char)
					* ft_strlen(tokenset->token[i]->value));
			if (!new)
				free_tokenset(tokenset, FAILED);
			ft_memcpy(new, tokenset->token[i]->value + 1,
				ft_strlen(tokenset->token[i]->value) - 1);
			new[ft_strlen(tokenset->token[i]->value) - 1] = '\0';
			free(tokenset->token[i]->value);
			tokenset->token[i]->value = new;
		}
		i++;
	}
}
