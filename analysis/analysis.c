/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:56:35 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/04 20:12:22 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"

//文字列中に指定の文字が何文字あるか数える
static int	count_letter(char *input, char c)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (input[i])
	{
		if (input[i] == c)
			count++;
		i++;
	}
	return (count);
}

//各行をトークン化する（具体）
static int	tokenize_command(char *command, t_tokenlist *tokenlist, int i)
{
	char	**array;
	int		j;

	tokenlist->size[i] = count_letter(command, ' ') + 1;
	array = ft_split(command, ' ');
	if (!array)
		return (FAILED);
	tokenlist->token[i] = (t_token *)malloc(sizeof(t_token)
			* tokenlist->size[i]);
	if (!tokenlist->token[i])
		return (free_array((void **)array), FAILED);
	j = 0;
	while (j < tokenlist->size[i] - 1)
	{
		tokenlist->token[i][j].value = ft_strdup(array[j]);
		if (!tokenlist->token[i][j].value)
			return (free_array((void **)array), free_values(tokenlist, i, j),
				FAILED);
		tokenlist->token[i][j].line = i;
		tokenlist->token[i][j].column = j;
		j++;
	}
	tokenlist->token[i][j].value = NULL;
	tokenlist->token[i][j].line = i;
	tokenlist->token[i][j].column = j;
	free_array((void **)array);
	return (SUCCESS);
}

//各行をトークン化する
static int	split_commands_to_tokens(char *input, t_tokenlist *tokenlist)
{
	char	**array;
	int		i;

	tokenlist->set_count = count_letter(input, '\n');
	array = ft_split(input, '\n');
	if (!array)
		return (FAILED);
	tokenlist->token = (t_token **)malloc(sizeof(t_token *)
			* tokenlist->set_count);
	if (!tokenlist->token)
		return (free_array((void **)array), FAILED);
	tokenlist->size = (int *)malloc(sizeof(int) * (tokenlist->set_count + 1));
	if (!tokenlist->size)
		return (free_array((void **)array),
			free_array((void **)tokenlist->token), FAILED);
	tokenlist->size[tokenlist->set_count] = 0;
	i = 0;
	while (i < tokenlist->set_count)
	{
		if (tokenize_command(array[i], tokenlist, i) == FAILED)
			return (free_array((void **)array),
				free_array((void **)tokenlist->token), FAILED);
		i++;
	}
	return (free_array((void **)array), SUCCESS);
}

static void	print_token(t_tokenlist *tokenlist)
{
	int			i;
	int			j;
	const char	*type_names[] = {"TOK_IDENTIFIER", "TOK_OPERATOR",
			"TOK_LITERAL", "TOK_REDIRECT", "TOK_PIPE", "TOK_END", "TOK_INVALID",
			NULL};

	i = 0;
	while (i < tokenlist->set_count)
	{
		j = 0;
		while (j < tokenlist->size[i])
		{
			printf("tokentype : %s\n", type_names[tokenlist->token[i][j].type]);
			printf("value : %s\n\n", tokenlist->token[i][j].value);
			j++;
		}
		i++;
	}
}

//字句解析と構文解析
t_tokenlist	*analysis(char *input)
{
	t_tokenlist	*tokenlist;

	tokenlist = (t_tokenlist *)malloc(sizeof(t_tokenlist));
	if (!tokenlist)
		malloc_failed();
	if (FAILED == split_commands_to_tokens(input, tokenlist))
	{
		free(tokenlist);
		malloc_failed();
	}
	lexical_analysis(tokenlist);
	print_token(tokenlist);
	return (tokenlist);
}
