/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:17:08 by okaname           #+#    #+#             */
/*   Updated: 2025/03/04 20:56:32 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	input(char **envp)
// {
// 	char	*line;

// 	line = NULL;
// 	while (1)
// 	{
// 		line = readline("minishell$");
// 		if (line == NULL)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		if (*line == '\0')
// 		{
// 			printf("\n");
// 			free(line);
// 			continue ;
// 		}
// 		add_history(line);
// 		free(line);
// 	}
// 	return (0);
// }

int	input(char **envp)
{
	char	*line;
	char	**command;

	line = NULL;
	while (1)
	{
		line = readline("minishell$");
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
		add_history(line);
		command = ft_split(line, ' ');
		free(line);
		if (command == NULL || command[0] == NULL)
		{
			free(command);
			continue ;
		}
		excute(command, envp);
	}
	return (0);
}
