/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokentype2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:05:45 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/10 18:01:24 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	check_assignment(char *value)
{
	int	i;

	if (!ft_isalpha(value[0]) && value[0] != '_')
		return (FAILED);
	i = 1;
	while (value[i] && value[i] != '=')
	{
		if (!ft_isalnum(value[0]) && value[i] != '_')
			return (FAILED);
		i++;
	}
	if (!value[i])
		return (FAILED);
	return (SUCCESS);
}

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
	else if (SUCCESS == check_env_var(token->value))
		token->type = TOK_ENV_VAR;
	else if (1)
		token->type = TOK_SEMICOLON;
	else if (SUCCESS == check_assignment(token->value))
		token->type = TOK_ASSIGNMENT;
	else
		token->type = TOK_WORD;
}
