/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:37:03 by okaname           #+#    #+#             */
/*   Updated: 2025/03/26 18:24:23 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_pipe(t_token *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while ((token[i]).value != NULL)
	{
		if (token->type == TOK_PIPE)
			count++;
		i++;
	}
	return (count);
}

static t_command	*token_to_cmd(t_token *token)
{
	int			cmd_count;
	t_command	*cmd;

	cmd_count = count_pipe(token) + 1;
	cmd = malloc(sizeof(t_command) * cmd_count);
	if (cmd == NULL)
		error_malloc(NULL, NULL);
	set_fd_in(&cmd, token);
	set_fd_out(&cmd, token);
	set_fd_err(&cmd, token);
	set_cmd(&cmd, token);
	return (cmd);
}

int	run_token(t_mini *minishell)
{
	t_tokenlist	*tokenlist;
	t_command	*cmd;
	int			i;

	printf("aaaa\n");
	tokenlist = analysis(minishell->input);
	printf("aaaa\n");
	i = 0;
	while ((*(tokenlist->token))[i] != NULL)
	{
		cmd = token_to_cmd((*(tokenlist->token))[i]);
	}
	return (0);
}
