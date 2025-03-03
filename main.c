/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:20:53 by okaname           #+#    #+#             */
/*   Updated: 2025/03/03 14:54:40 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL || strlen(line) == 0)
		{
			free(line);
			break ;
		}
		printf("line is '%s'\n", line);
		add_history(line);
		free(line);
	}
	printf("exit\n");
	return (0);
}
