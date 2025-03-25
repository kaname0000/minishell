/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:19:09 by okaname           #+#    #+#             */
/*   Updated: 2025/03/25 22:25:51 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_fd_in(t_command **cmd, t_token *token)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = 0;
	while ((token[i])->value == NULL)
	{
		if ((token[i])->type == TOK_PIPE)
			pipe_count++;
	}
}
