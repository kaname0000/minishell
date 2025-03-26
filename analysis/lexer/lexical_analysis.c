/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 01:04:00 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/26 17:07:41 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

const char	*token_types[] = {"TOK_WORD", "TOK_ASSIGNMENT", "TOK_LITERAL",
		"TOK_BUILTIN", "TOK_PIPE", "TOK_SEMICOLON", "TOK_AMPERSAND",
		"TOK_REDIR_IN", "TOK_REDIR_OUT", "TOK_REDIR_APPEND", "TOK_HEREDOC",
		"TOK_SQUOTE_START", "TOK_SQUOTE_IN", "TOK_SQUOTE_END",
		"TOK_DQUOTE_START", "TOK_DQUOTE_IN", "TOK_DQUOTE_END", "TOK_BACKSLASH",
		"TOK_LPAREN", "TOK_RPAREN", "TOK_ENV_VAR", "TOK_ENV_VAR_NAME",
		"TOK_EXIT_STATUS", "TOK_NEWLINE", "TOK_NULL", "TOK_EOF", "TOK_SPLIT",
		"UNSIGNED"};

static void	print_tokenset(t_tokenset *tokenset)
{
	int		i;
	t_token	*token;

	i = 0;
	while (i < tokenset->count)
	{
		token = tokenset->token[i];
		if (!ft_strcmp(token->value, "\n"))
			printf("%-20s \\n           \n", token_types[token->type]);
		else
			printf("%-20s %-12s\n", token_types[token->type], token->value);
		i++;
	}
}

// 字句解析
void	lexical_analysis(char *input, t_tokenlist *tokenlist)
{
	int			i;
	int			j;
	t_tokenset	*tokenset;

	tokenlist->input = input;
	get_tokens(tokenlist);
	init_token(tokenlist);
	i = 0;
	while (i < tokenlist->set_count)
	{
		j = 0;
		while (j < tokenlist->token_count[i])
		{
			check_tokentype(tokenlist->token[i][j], tokenlist);
			j++;
		}
		i++;
	}
	traverse_token_list(tokenlist);
	tokenset = reshape_tokenlist(tokenlist);
	print_tokenset(tokenset);
}
