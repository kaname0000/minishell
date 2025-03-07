/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:56:35 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/06 21:33:29 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//テスト用出力関数
static void	print_token(t_tokenlist *tokenlist)
{
	int	i;
	int	j;

	// const char	*type_names[] = {"TOK_IDENTIFIER", "TOK_OPERATOR",
	// 		"TOK_LITERAL", "TOK_REDIRECT", "TOK_PIPE", "TOK_END", "TOK_INVALID",
	// 		NULL};
	i = 0;
	while (i < tokenlist->set_count)
	{
		j = 0;
		while (j < tokenlist->token_count[i])
		{
			printf("tokentype : %d\n", tokenlist->token[i][j].type);
			if (!tokenlist->token[i][j].value)
				printf("value : %s\n\n", tokenlist->token[i][j].value);
			else if (tokenlist->token[i][j].value[0] == '\n')
				printf("value : \\n\n\n");
			else
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
		free_tokenlist(tokenlist);
	lexical_analysis(input, tokenlist);
	print_token(tokenlist);
	// syntax_analysis(tokenlist);
	return (tokenlist);
}
