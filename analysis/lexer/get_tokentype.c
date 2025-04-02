/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokentype.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:11:59 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/02 19:58:07 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	simple_check(t_token *token, t_token *pre_token, char *cmp)
{
	if (pre_token)
	{
		if (!ft_strcmp(token->value, cmp) && !token->squote && !token->dquote
			&& pre_token->type != TOK_BACKSLASH)
			return (SUCCESS);
		return (FAILED);
	}
	else
	{
		if (!ft_strcmp(token->value, cmp) && !token->squote && !token->dquote)
			return (SUCCESS);
		return (FAILED);
	}
}

int	check_env(t_token *token, t_token *pre_token, char *dollar)
{
	if (pre_token)
	{
		if (!ft_strcmp(token->value, dollar) && !token->squote
			&& pre_token->type != TOK_BACKSLASH)
			return (SUCCESS);
		return (FAILED);
	}
	else
	{
		if (!ft_strcmp(token->value, dollar) && !token->squote)
			return (SUCCESS);
		return (FAILED);
	}
}

static void	get_tokentype2(t_token *token, t_token *pre_token)
{
	if (simple_check(token, pre_token, "\n"))
		token->type = TOK_NEWLINE;
	// else if (pre_token && simple_check(token, pre_token, "="))
	// {
	// 	pre_token->type = TOK_ENV_VAR_NAME;
	// 	token->type = TOK_ASSIGNMENT;
	// }
	// else if (pre_token && pre_token->type == TOK_ASSIGNMENT)
	// 	token->type = TOK_LITERAL;
	else if (check_env(token, pre_token, "$?"))
		token->type = TOK_EXIT_STATUS;
	else if (check_env(token, pre_token, "$"))
		token->type = TOK_ENV_VAR;
	else if (pre_token && pre_token->type == TOK_ENV_VAR)
		token->type = TOK_ENV_VAR_NAME;
	else if (simple_check(token, NULL, "echo") || simple_check(token, NULL,
			"cd") || simple_check(token, NULL, "pwd") || simple_check(token,
			NULL, "export") || simple_check(token, NULL, "unset")
		|| simple_check(token, NULL, "env") || simple_check(token, NULL,
			"exit"))
		token->type = TOK_BUILTIN;
	else
		token->type = TOK_WORD;
}

void	get_tokentype(t_token *token, t_token *pre_token)
{
	if (token->type != UNSIGNED)
		return ;
	else if (!token->value)
		token->type = TOK_NULL;
	else if (simple_check(token, pre_token, "|"))
		token->type = TOK_PIPE;
	// else if (simple_check(token, pre_token, ";"))
	// 	token->type = TOK_SEMICOLON;
	// else if (simple_check(token, pre_token, "&"))
	// 	token->type = TOK_AMPERSAND;
	else if (simple_check(token, pre_token, "<"))
		token->type = TOK_REDIR_IN;
	else if (simple_check(token, pre_token, ">"))
		token->type = TOK_REDIR_OUT;
	else if (simple_check(token, pre_token, "<<"))
		token->type = TOK_HEREDOC;
	else if (simple_check(token, pre_token, ">>"))
		token->type = TOK_REDIR_APPEND;
	// else if (simple_check(token, pre_token, "("))
	// 	token->type = TOK_LPAREN;
	// else if (simple_check(token, pre_token, ")"))
	// 	token->type = TOK_RPAREN;
	else
		get_tokentype2(token, pre_token);
	if (pre_token)
	{
		token->squote = pre_token->squote;
		token->dquote = pre_token->dquote;
	}
}
