/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:02:03 by yookamot          #+#    #+#             */
/*   Updated: 2025/03/06 20:43:18 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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

// token_typeの割当
void	check_token(t_token *token)
{
	if (!token->value || token->value[0] == '\0')
		token->type = TOK_EOF;
	else if (!ft_strcmp(token->value, "<"))
		token->type = TOK_REDIR_IN;
	else if (!ft_strcmp(token->value, ">"))
		token->type = TOK_REDIR_OUT;
	else if (!ft_strcmp(token->value, "<<"))
		token->type = TOK_HEREDOC;
	else if (!ft_strcmp(token->value, ">>"))
		token->type = TOK_REDIR_APPEND;
	else if (!ft_strcmp(token->value, "|"))
		token->type = TOK_PIPE;
	else if (!ft_strcmp(token->value, "\\"))
		token->type = TOK_BACKSLASH;
	else if (!ft_strcmp(token->value, "("))
		token->type = TOK_LPAREN;
	else if (!ft_strcmp(token->value, ")"))
		token->type = TOK_RPAREN;
	else if (!ft_strcmp(token->value, "$?"))
		token->type = TOK_EXIT_STATUS;
	else if (!ft_strcmp(token->value, "\n"))
		token->type = TOK_NEWLINE;
	else
		token->type = TOK_EXIT_STATUS;
}
