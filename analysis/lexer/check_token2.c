/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:05:45 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/08 16:54:57 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// static int	check_literal(char *value)
// {
// 	int	len;

// 	if (!value || value[0] == '\0')
// 		return (1);
// 	len = ft_strlen(value);
// 	if ((value[0] == '\'' && value[len - 1] == '\'') || (value[0] == '\"'
// 			&& value[len - 1] == '\"'))
// 		return (0);
// 	return (1);
// }

// static int	check_invalid(char *value)
// {
// 	int	len;

// 	if (!value || value[0] == '\0')
// 		return (1);
// 	len = ft_strlen(value);
// 	if (value[0] == '\'' && value[len - 1] != '\'')
// 		return (0);
// 	if (value[0] == '\"' && value[len - 1] != '\"')
// 		return (0);
// 	if (value[len - 1] == '\\')
// 		return (0);
// 	return (1);
// }

void	check_token2(t_token *token)
{
	if (!ft_strcmp(token->value, "echo") || !ft_strcmp(token->value, "cd")
		|| !ft_strcmp(token->value, "pwd") || !ft_strcmp(token->value, "export")
		|| !ft_strcmp(token->value, "unset") || !ft_strcmp(token->value, "env")
		|| !ft_strcmp(token->value, "exit"))
		token->type = TOK_BUILTIN;
	else if (!ft_strcmp(token->value, "\\"))
		token->type = TOK_BACKSLASH;
	else if (1)
		token->type = TOK_SQUOTE;
	else if (1)
		token->type = TOK_DQUOTE;
	else if (1)
		token->type = TOK_ENV_VAR;
	else if (1)
		token->type = TOK_SEMICOLON;
	else if (1)
		token->type = TOK_ASSIGNMENT;
	else
		token->type = TOK_WORD;
}
