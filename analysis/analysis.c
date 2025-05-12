/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:56:35 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/12 18:20:04 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"

const char	*token_types[] = {"TOK_WORD", "TOK_BUILTIN", "TOK_PIPE",
		"TOK_REDIR_IN", "TOK_REDIR_OUT", "TOK_REDIR_APPEND", "TOK_HEREDOC",
		"TOK_SQUOTE_START", "TOK_SQUOTE_IN", "TOK_SQUOTE_END",
		"TOK_DQUOTE_START", "TOK_DQUOTE_IN", "TOK_DQUOTE_END", "TOK_NEWLINE",
		"TOK_NULL", "TOK_SPLIT", "UNSIGNED"};

void	print_tokenset(t_tokenset *tokenset)
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

//字句解析と構文解析
t_tokenset	*analysis(char *input, t_mini *mini)
{
	t_tokenlist	*tokenlist;
	t_tokenset	*tokenset;

	if (!input)
		return (NULL);
	tokenlist = (t_tokenlist *)malloc(sizeof(t_tokenlist));
	if (!tokenlist)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	tokenlist->input = ft_strdup(input);
	if (!tokenlist->input)
		free_tokenlist(tokenlist, NULL, NULL, FAILED);
	tokenlist->sflag = NULL;
	tokenlist->dflag = NULL;
	tokenset = lexical_analysis(tokenlist, mini);
	if (!syntax_analysis(tokenset))
		return (NULL);
	print_tokenset(tokenset);
	return (tokenset);
}
