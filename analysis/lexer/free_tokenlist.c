/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokenlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:28:35 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/16 22:06:16 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	malloc_failed(void)
{
	perror("Memory allocation failed");
	exit(EXIT_FAILURE);
}

static void	free_split_token(t_token *token, int key)
{
	int	i;

	if (token->count == 1 && key == SUCCESS)
		return ;
	if (!token->split_token)
	{
		free(token->value);
		free(token);
		return ;
	}
	i = 0;
	while (i < token->count)
	{
		if (token->split_token[i])
			free_split_token(token->split_token[i], key);
		i++;
	}
	free(token->split_token);
	free(token->value);
	free(token);
}

static void	cleanup_split_token(t_tokenlist *tokenlist, int key)
{
	int	i;
	int	j;

	if (!tokenlist || !tokenlist->token)
		return ;
	i = 0;
	while (i < tokenlist->set_count)
	{
		if (tokenlist->token[i])
		{
			j = 0;
			while (j < tokenlist->token_count[i])
			{
				if (tokenlist->token[i][j])
				{
					if (key == FAILED || tokenlist->token[i][j]->count != 1)
						free_split_token(tokenlist->token[i][j], key);
					tokenlist->token[i][j] = NULL;
				}
				j++;
			}
			free(tokenlist->token[i]);
			tokenlist->token[i] = NULL;
		}
		i++;
	}
	if (tokenlist->sflag)
		free(tokenlist->sflag);
	if (tokenlist->dflag)
		free(tokenlist->dflag);
	free(tokenlist->token);
	free(tokenlist->token_count);
	free(tokenlist);
	if (key == FAILED)
		free(tokenlist->input);
}

void	free_tokenlist(t_tokenlist *tokenlist, char **array1, char **array2,
		int key)
{
	if (!tokenlist)
	{
		free_array(array1);
		free_array(array2);
		if (key == FAILED)
			malloc_failed();
		return ;
	}
	free_array(array1);
	free_array(array2);
	cleanup_split_token(tokenlist, key);
	if (key == FAILED)
		malloc_failed();
}
