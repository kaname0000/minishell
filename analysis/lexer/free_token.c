/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:28:35 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/07 14:24:02 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_token(t_tokenlist *tokenlist)
{
	int	i;

	i = 0;
	if (!tokenlist->token)
		return ;
	while (i < tokenlist->set_count)
	{
		free(tokenlist->token[i]);
		i++;
	}
	free(tokenlist->token);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return ;
}

void	malloc_failed(void)
{
	perror("Memory allocation failed");
	exit(EXIT_FAILURE);
}

static void	free_values(t_tokenlist *tokenlist)
{
	int	i;
	int	j;

	i = 0;
	while (i < tokenlist->set_count)
	{
		if (!tokenlist->token[i])
			return (free(tokenlist->token_count), free_token(tokenlist),
				free(tokenlist), malloc_failed());
		j = 0;
		while (j < tokenlist->token_count[i])
		{
			if (!tokenlist->token[i][j].value && j != tokenlist->token_count[i]
				- 1)
				return (free(tokenlist->token_count), free_token(tokenlist),
					free(tokenlist), malloc_failed());
			free(tokenlist->token[i][j].value);
			j++;
		}
		i++;
	}
}

void	free_tokenlist(t_tokenlist *tokenlist)
{
	if (!tokenlist)
		malloc_failed();
	if (!tokenlist->token)
	{
		free(tokenlist);
		malloc_failed();
	}
	if (!tokenlist->token_count)
	{
		free_token(tokenlist);
		free(tokenlist);
		malloc_failed();
	}
	free_values(tokenlist);
	free(tokenlist->token_count);
	free_token(tokenlist);
	free(tokenlist);
}
