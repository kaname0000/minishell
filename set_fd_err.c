/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:02:13 by okaname           #+#    #+#             */
/*   Updated: 2025/03/26 16:55:44 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_fd_err(t_command **cmd, t_token *token)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = 0;
	cmd[pipe_count]->fd_err = 2;
	while ((token[i]).value == NULL)
	{
		if ((token[i]).type == TOK_PIPE)
		{
			pipe_count++;
			cmd[pipe_count]->fd_err = 2;
		}
		i++;
	}
	return (0);
}
