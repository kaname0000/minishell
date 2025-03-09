/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:56:35 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/09 20:30:21 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//テスト用出力関数
static void	print_token(t_tokenlist *tokenlist)
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
}

//字句解析と構文解析
t_tokenlist	*analysis(char *input)
{
	t_tokenlist	*tokenlist;

	tokenlist = (t_tokenlist *)malloc(sizeof(t_tokenlist));
	if (!tokenlist)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	lexical_analysis(input, tokenlist);
	print_token(tokenlist);
	// syntax_analysis(tokenlist);
	return (tokenlist);
}
