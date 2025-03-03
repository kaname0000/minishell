/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:56:35 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/03 18:44:30 by yookamot         ###   ########.fr       */
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
static void	tokenize_command(char *command, t_tokenlist *tokenlist, int i)
{
	char	**array;
	int		j;

	tokenlist->size[i] = count_letter(command, ' ');
	array = ft_split(command, ' ');
	tokenlist->token[i] = (t_token *)malloc(sizeof(t_token)
			* tokenlist->size[i]);
	if (!array || !tokenlist[i])
		// malloc fail
		return ;
	j = 0;
	while (j < tokenlist->size[i])
	{
		tokenlist->token[i][j]->value = array[j];
		tokenlist->token[i][j]->line = i;
		tokenlist->token[i][j]->column = j;
		j++;
	}
	free_array(array);
}

//各行をトークン化する
static void	split_commands_to_tokens(char *input, t_tokenlist *tokenlist)
{
	char	**array;
	int		i;

	tokenlist->set_count = count_letter(input, '\n');
	array = ft_split(input, '\n');
	tokenlist->token = (t_token **)malloc(sizeof(t_token *)
			* tokenlist->set_count);
	tokenlist->size = (int *)malloc(sizeof(int) * (tokenlist->set_count + 1));
	if (!array || !tokenlist->token || !tokenlist->size)
		// malloc fail
		return ;
	tokenlist->size[tokenlist->set_count] = 0;
	i = 0;
	while (i < tokenlist->set_count)
	{
		tokenize_command(array[i], tokenlist, i);
		i++;
	}
	free_array(array);
}

//字句解析と構文解析
void	analysis(char *input)
{
	t_tokenlist	*tokenlist;
	int			i;
	int			count;

	tokenlist = (t_tokenlist *)malloc(sizeof(t_tokenlist));
	if (!tokenlist)
		// malloc fail
		return ;
	split_commands_to_tokens(input, tokenlist);
	lexical_analysis(tokenlist);
}
