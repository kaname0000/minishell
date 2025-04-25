/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:53:09 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/23 20:41:07 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	init_token(t_token *token, char *str, t_tokenlist *tokenlist)
{
	if (str)
	{
		token->value = ft_strdup(str);
		if (!token->value)
			free_tokenlist(tokenlist, NULL, NULL, FAILED);
	}
	else
		token->value = NULL;
	token->split_token = NULL;
	token->squote = 0;
	token->dquote = 0;
	token->count = 1;
	token->type = UNSIGNED;
}
