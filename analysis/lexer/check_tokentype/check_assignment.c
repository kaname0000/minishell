/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_assignment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:57:13 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/13 18:47:45 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_tokentype.h"

static int	check_valid_word(char *value, int i)
{
	if (!value[i + 1])
		return (FAILED);
	while (i > 0)
	{
		if (!ft_isalnum(value[i]) && value[i] != '_')
			return (FAILED);
		i--;
	}
	if (!ft_isalpha(value[0]) || value[0] != '_')
		return (FAILED);
	return (SUCCESS);
}

static int	count_assignment(t_token *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token->value[i])
	{
		if (token->value[i] == '=')
		{
			count++;
			if (token->squote[i] || token->dquote[i]
				|| !check_valid_word(token->value, i))
				return (FAILED);
			else
				return (count);
		}
		i++;
	}
	return (FAILED);
}

int	check_assignment(t_token *token, t_tokenlist *tokenlist)
{
	int	count;

	count = count_assignment(token);
	if (!count)
		return (FAILED);
	split_token(tokenlist, ft_strdup("="), token, count);
	if (token->type != TOK_SPLIT)
		return (FAILED);
	return (SUCCESS);
}
