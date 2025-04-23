/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:26:44 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/23 21:45:33 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

// tokenのほうでquoteを消すのに応じて、inputのquoteを削除
void	reset_input(t_tokenset *tokenset, int i, int j, int key)
{
	char	*new;
	int		k;
	int		l;

	if (key == FRONT || (key == BACK && tokenset->token[i
			+ 1]->type != TOK_DQUOTE_START && tokenset->token[i
			+ 1]->type != TOK_SQUOTE_START))
		return ;
	new = (char *)malloc(sizeof(char) * (ft_strlen(tokenset->input) - 1));
	if (!new)
		free_tokenset(tokenset, FAILED);
	k = 0;
	while (k < j)
	{
		new[k] = tokenset->input[k];
		k++;
	}
	j++;
	l = 0;
	while (l < (int)ft_strlen(tokenset->token[i + 1]->value))
	{
		new[k++] = tokenset->input[j++];
		l++;
	}
	j++;
	while (tokenset->input[j])
		new[k++] = tokenset->input[j++];
	new[k] = '\0';
	free(tokenset->input);
	tokenset->input = new;
}
