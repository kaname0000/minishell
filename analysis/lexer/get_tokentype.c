/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokentype.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:11:59 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/05 01:32:59 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	simple_check(t_token *token, char *cmp)
{
	if (!ft_strcmp(token->value, cmp) && !token->squote && !token->dquote)
		return (SUCCESS);
	return (FAILED);
}

static void	get_tokentype2(t_token *token, t_token *pre_token)
{
	if (!ft_strcmp(token->value, "\n"))
		token->type = TOK_NEWLINE;
	else if (!ft_strcmp(token->value, "$?") && !token->squote)
		token->type = TOK_EXIT_STATUS;
	else if (!ft_strcmp(token->value, "$") && !token->squote)
		token->type = TOK_ENV_VAR;
	else if (pre_token && pre_token->type == TOK_ENV_VAR)
		token->type = TOK_ENV_VAR_NAME;
	else if (simple_check(token, "echo") || simple_check(token, "cd")
		|| simple_check(token, "pwd") || simple_check(token, "export")
		|| simple_check(token, "unset") || simple_check(token, "env")
		|| simple_check(token, "exit"))
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
	else if (simple_check(token, "|"))
		token->type = TOK_PIPE;
	else if (simple_check(token, "<"))
		token->type = TOK_REDIR_IN;
	else if (simple_check(token, ">"))
		token->type = TOK_REDIR_OUT;
	else if (simple_check(token, "<<"))
		token->type = TOK_HEREDOC;
	else if (simple_check(token, ">>"))
		token->type = TOK_REDIR_APPEND;
	else
		get_tokentype2(token, pre_token);
	if (pre_token)
	{
		token->squote = pre_token->squote;
		token->dquote = pre_token->dquote;
	}
}
