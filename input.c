/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:17:08 by okaname           #+#    #+#             */
/*   Updated: 2025/03/03 17:07:43 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input(void)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("");
		if (line == NULL)
		{
			free(line);
			break ;
		}
		if (*line == '\0')
		{
			printf("\n");
			free(line);
			continue ;
		}
		printf("line is %s\n", line);
		add_history(line);
		free(line);
	}
	return (0);
}
