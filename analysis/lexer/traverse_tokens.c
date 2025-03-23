/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamotoyota <okamotoyota@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:08:38 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/18 01:24:44 by okamotoyota      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

const char	*token_types[] = {"TOK_WORD", "TOK_ASSIGNMENT", "TOK_LITERAL",
		"TOK_BUILTIN", "TOK_PIPE", "TOK_SEMICOLON", "TOK_AMPERSAND",
		"TOK_REDIR_IN", "TOK_REDIR_OUT", "TOK_REDIR_APPEND", "TOK_HEREDOC",
		"TOK_SQUOTE_START", "TOK_SQUOTE_IN", "TOK_SQUOTE_END",
		"TOK_DQUOTE_START", "TOK_DQUOTE_IN", "TOK_DQUOTE_END", "TOK_BACKSLASH",
		"TOK_LPAREN", "TOK_RPAREN", "TOK_ENV_VAR", "TOK_ENV_VAR_NAME",
		"TOK_EXIT_STATUS", "TOK_NEWLINE", "TOK_NULL", "TOK_EOF", "TOK_SPLIT"};

static void	process_token(t_token *token)
{
	static t_token	*pre_token;
	static t_token	*pre_pre_token;

	if (token->count == 1)
	{
		set_quote_info(token, pre_token, pre_pre_token);
		printf("A\n");
		get_tokentype(token, pre_token);
		printf("A\n");
		if (!ft_strcmp(token->value, "\n"))
			printf("%-20s \\n           \n", token_types[token->type]);
		else
			printf("%-20s %-12s\n", token_types[token->type], token->value);
		printf("A\n");
		if (pre_token && pre_pre_token)
			pre_pre_token = pre_token;
		printf("A\n");
		if (token)
			pre_token = token;
	}
}

static void	traverse_tokens(t_token *token, int depth)
{
	int	i;

	process_token(token);
	if (token->count > 1)
	{
		i = 0;
		while (i < token->count)
		{
			traverse_tokens(token->split_token[i], depth + 1);
			i++;
		}
	}
}

void	traverse_token_list(t_tokenlist *tokenlist)
{
	int	i;
	int	j;

	i = 0;
	while (i < tokenlist->set_count)
	{
		j = 0;
		while (j < tokenlist->token_count[i])
		{
			traverse_tokens(tokenlist->token[i][j], 0);
			j++;
		}
		i++;
	}
}
