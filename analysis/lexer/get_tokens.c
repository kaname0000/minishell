/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:30:13 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/09 22:01:55 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//各行に含まれる単語数のカウント
static int	count_word(char **array)
{
	int	count;

	count = 0;
	while (array[count])
		count++;
	count++;
	return (count);
}

//各行をトークン化する（valueの値）
static void	tokenize_command(char *command, t_tokenlist *tokenlist, int i,
		char **lines)
{
	char	**array;
	int		j;

	array = ft_split_custom(command, tokenlist, i);
	array = check_single_and_double_quote(array);
	if (!array)
		return (tokenlist->token[i] = NULL, free_tokenlist(tokenlist, lines,
				NULL, FAILED));
	tokenlist->token_count[i] = count_word(array);
	if (!array)
		free_tokenlist(tokenlist, lines, array, FAILED);
	tokenlist->token[i] = (t_token **)malloc(sizeof(t_token *)
			* tokenlist->token_count[i]);
	if (!tokenlist->token[i])
		free_tokenlist(tokenlist, lines, array, FAILED);
	j = 0;
	while (j < tokenlist->token_count[i] - 1)
	{
		tokenlist->token[i][j] = (t_token *)malloc(sizeof(t_token));
		if (!tokenlist->token[i][j])
			free_tokenlist(tokenlist, lines, array, FAILED);
		tokenlist->token[i][j]->value = ft_strdup(array[j]);
		if (!tokenlist->token[i][j]->value)
			free_tokenlist(tokenlist, lines, array, FAILED);
		j++;
	}
	tokenlist->token[i][j] = (t_token *)malloc(sizeof(t_token));
	if (!tokenlist->token[i][j])
		free_tokenlist(tokenlist, lines, array, FAILED);
	tokenlist->token[i][j]->value = NULL;
	return (free_array(array));
}

//行数のカウント
static int	count_line(char *input)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

//各行をトークン化する
void	get_tokens(char *input, t_tokenlist *tokenlist)
{
	char	**array;
	int		i;

	tokenlist->set_count = count_line(input);
	array = ft_split(input, '\n');
	if (!array)
		return (tokenlist->token = NULL, free_tokenlist(tokenlist, NULL, NULL,
				FAILED));
	tokenlist->token = (t_token ***)malloc(sizeof(t_token **)
			* tokenlist->set_count);
	if (!tokenlist->token)
		free_tokenlist(tokenlist, array, NULL, FAILED);
	tokenlist->token_count = (int *)malloc(sizeof(int) * (tokenlist->set_count
				+ 1));
	if (!tokenlist->token_count)
		free_tokenlist(tokenlist, array, NULL, FAILED);
	tokenlist->token_count[tokenlist->set_count] = 0;
	i = 0;
	while (i < tokenlist->set_count)
	{
		tokenize_command(array[i], tokenlist, i, array);
		i++;
	}
	check_single_and_double_quote(tokenlist, array);
	return (free_array(array));
}
