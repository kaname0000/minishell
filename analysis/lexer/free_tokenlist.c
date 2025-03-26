/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokenlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:28:35 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/26 12:45:47 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
}

static void	malloc_failed(void)
{
	perror("Memory allocation failed");
	exit(EXIT_FAILURE);
}

static void	free_token_and_value(t_tokenlist *tokenlist, int key)
{
	int	i;
	int	j;

	i = 0;
	while (i < tokenlist->set_count)
	{
		j = 0;
		while (j < tokenlist->token_count[i])
		{
			if (tokenlist->token[i][j])
			{
				if (tokenlist->token[i][j]->value)
					free(tokenlist->token[i][j]->value);
				free(tokenlist->token[i][j]);
			}
			j++;
		}
		free(tokenlist->token[i]);
		i++;
	}
	free(tokenlist->token);
	free(tokenlist->token_count);
	free(tokenlist);
	if (key == FAILED)
		malloc_failed();
}

void	free_tokenlist(t_tokenlist *tokenlist, char **array1, char **array2,
		int key)
{
	free_array(array1);
	free_array(array2);
	if (!tokenlist)
		malloc_failed();
	if (!tokenlist->token)
	{
		free(tokenlist);
		malloc_failed();
	}
	if (!tokenlist->token_count)
	{
		free(tokenlist->token);
		free(tokenlist);
		malloc_failed();
	}
	free_token_and_value(tokenlist, key);
}

void	free_tokenset(t_tokenset *tokenset)
{
	free(tokenset);
}