/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:05:03 by okaname           #+#    #+#             */
/*   Updated: 2025/03/26 16:56:36 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_count(t_command **cmd, t_token *token)
{
	int	i;
	int	count;
	int	pipe_count;

	i = 0;
	count = 0;
	pipe_count = 0;
	while ((token[i]).value == NULL)
	{
		if ((token[i]).type == TOK_PIPE)
		{
			cmd[pipe_count]->cmd = malloc(sizeof(char *) * (count + 1));
			if (cmd[pipe_count]->cmd == NULL)
				error_malloc(NULL, NULL);
			count = 0;
			pipe_count++;
		}
		else if ((token[i]).type == TOK_REDIR_APPEND
			|| (token[i]).type == TOK_REDIR_IN
			|| (token[i]).type == TOK_REDIR_OUT
			|| (token[i]).type == TOK_HEREDOC)
		{
			i += 2;
			continue ;
		}
		else if ((token[i]).type == TOK_WORD)
			count++;
		i++;
	}
	return (0);
}

int	set_cmd(t_command **cmd, t_token *token)
{
	int	i;
	int	pipe_count;
	int	count;

	i = 0;
	pipe_count = 0;
	count = 0;
	while ((token[i]).value == NULL)
	{
		if ((token[i]).type == TOK_PIPE)
		{
			count = 0;
			pipe_count++;
		}
		else if ((token[i]).type == TOK_REDIR_APPEND
			|| (token[i]).type == TOK_REDIR_IN
			|| (token[i]).type == TOK_REDIR_OUT
			|| (token[i]).type == TOK_HEREDOC)
		{
			i += 2;
			continue ;
		}
		else if ((token[i]).type == TOK_WORD)
		{
			count++;
			cmd[pipe_count]->cmd[count] = token->value;
		}
		i++;
	}
	return (0);
}
