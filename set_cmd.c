/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 01:12:53 by okaname           #+#    #+#             */
/*   Updated: 2025/04/06 17:16:56 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_count(t_command **cmd, t_token **token)
{
	int	i;
	int	count;
	int	pipe_count;

	i = 0;
	count = 0;
	pipe_count = 0;
	while (1)
	{
		if ((token[i])->type == TOK_PIPE || (token[i])->type == TOK_NULL)
		{
			cmd[pipe_count]->cmd = malloc(sizeof(char *) * (count + 1));
			if (cmd[pipe_count]->cmd == NULL)
				error_malloc(NULL, NULL);
			cmd[pipe_count]->cmd[count] = NULL;
			count = 0;
			pipe_count++;
			if ((token[i])->type == TOK_NULL)
				break ;
		}
		else if ((token[i])->type == TOK_REDIR_APPEND
			|| (token[i])->type == TOK_REDIR_IN
			|| (token[i])->type == TOK_REDIR_OUT
			|| (token[i])->type == TOK_HEREDOC)
		{
			i += 2;
			continue ;
		}
		else if ((token[i])->type == TOK_WORD)
			count++;
		i++;
	}
	return (0);
}

static void	set_here_doc(t_command **cmd, t_token **token)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = 0;
	while ((token[i])->value != NULL)
	{
		if ((token[i])->type == TOK_PIPE)
			pipe_count++;
		else if ((token[i])->type == TOK_HEREDOC)
			here_doc((token[i + 1])->value, &(cmd[pipe_count]->fd_in));
		i++;
	}
}

int	set_cmd(t_command **cmd, t_token **token)
{
	int	i;
	int	pipe_count;
	int	count;

	i = 0;
	pipe_count = 0;
	count = 0;
	cmd_count(cmd, token);
	set_here_doc(cmd, token);
	while ((token[i])->value != NULL)
	{
		if ((token[i])->type == TOK_PIPE)
		{
			count = 0;
			pipe_count++;
		}
		else if ((token[i])->type == TOK_REDIR_APPEND
			|| (token[i])->type == TOK_REDIR_IN
			|| (token[i])->type == TOK_REDIR_OUT
			|| (token[i])->type == TOK_HEREDOC)
		{
			i += 2;
			continue ;
		}
		else if ((token[i])->type == TOK_WORD
			|| (token[i])->type == TOK_DQUOTE_IN
			|| (token[i])->type == TOK_SQUOTE_IN)
		{
			cmd[pipe_count]->cmd[count] = ft_strdup(token[i]->value);
			count++;
		}
		i++;
	}
	return (0);
}
