/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:56:35 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/14 05:32:50 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//テスト用出力関数
void	print_token(t_tokenlist *tokenlist)
{
	int	i;
	int	j;

	// const char	*type_names[] = {TOK_WORD, TOK_ASSIGNMENT, TOK_BUILTIN,
	// 		TOK_PIPE, TOK_SEMICOLON, TOK_AMPERSAND, TOK_REDIR_IN, TOK_REDIR_OUT,
	// 		TOK_REDIR_APPEND, TOK_HEREDOC, TOK_SQUOTE, TOK_DQUOTE,
	// 		TOK_BACKSLASH, TOK_LPAREN, TOK_RPAREN, TOK_ENV_VAR, TOK_EXIT_STATUS,
	// 		TOK_NEWLINE, TOK_EOF};
	i = 0;
	while (i < tokenlist->set_count)
	{
		j = 0;
		while (j < tokenlist->token_count[i])
		{
			// printf("tokentype : %s\n",
			// type_names[tokenlist->token[i][j].type]);
			if (!tokenlist->token[i][j]->value)
				printf("value : %s\n\n", tokenlist->token[i][j]->value);
			else if (tokenlist->token[i][j]->value[0] == '\n')
				printf("value : \\n\n\n");
			else
				printf("value : %s\n\n", tokenlist->token[i][j]->value);
			j++;
		}
		i++;
	}
	printf("set_count = %d, token_count = {%d, %d}\n", tokenlist->set_count,
		tokenlist->token_count[0], tokenlist->token_count[1]);
}

//字句解析と構文解析
t_tokenlist	*analysis(char *input)
{
	t_tokenlist	*tokenlist;

	tokenlist = (t_tokenlist *)malloc(sizeof(t_tokenlist));
	if (!tokenlist)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	lexical_analysis(input, tokenlist);
	// syntax_analysis(tokenlist);
	return (tokenlist);
}
