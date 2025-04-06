/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:37:03 by okaname           #+#    #+#             */
/*   Updated: 2025/04/06 17:43:07 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_pipe(t_token **token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while ((token[i])->value != NULL)
	{
		if (token[i]->type == TOK_PIPE)
			count++;
		i++;
	}
	return (count);
}

static t_command	**token_to_cmd(t_token **token)
{
	int			cmd_count;
	t_command	**cmd;
	int			i;

	cmd_count = count_pipe(token) + 1;
	cmd = (t_command **)malloc(sizeof(t_command *) * (cmd_count + 1));
	if (cmd == NULL)
		error_malloc(NULL, NULL);
	i = 0;
	while (i < cmd_count)
	{
		cmd[i] = (t_command *)malloc(sizeof(t_command));
		if (cmd[i] == NULL)
			error_malloc(NULL, NULL);
		cmd[i]->fd_in = 0;
		cmd[i]->fd_out = 1;
		i++;
	}
	cmd[cmd_count] = NULL;
	set_cmd(cmd, token);
	if (cmd_count > 1)
		conect_pipe(cmd);
	return (cmd);
}

int	run_token(t_mini *mini)
{
	t_tokenset	*tokenlist;
	int			i;
	int			count;
	int			*pid;

	i = 0;
	count = 0;
	pid = malloc(sizeof(int) * 1024);
	tokenlist = analysis(mini->input);
	mini->cmd = token_to_cmd(tokenlist->token);
	while (1)
	{
		if (tokenlist->token[i]->type == TOK_PIPE)
			make_prosses(mini, tokenlist, count++, &pid);
		else if (tokenlist->token[i]->type == TOK_NULL)
		{
			make_prosses(mini, tokenlist, count, &pid);
			break ;
		}
		i++;
	}
	free(pid);
	return (0);
}
