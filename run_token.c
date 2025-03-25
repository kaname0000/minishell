/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:37:03 by okaname           #+#    #+#             */
/*   Updated: 2025/03/25 22:23:17 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_pipe(t_token *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while ((token[i])->value != NULL)
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
}

int	run_token(t_mini *minishell)
{
	t_tokenlist	*tokenlist;
	int			i;

	tokenlist = analysis(minishell->input);
	i = 0;
	while ((*(tokenlist->token))[i] != NULL)
	{
	}
}
