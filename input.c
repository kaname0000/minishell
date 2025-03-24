/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:17:08 by okaname           #+#    #+#             */
/*   Updated: 2025/03/24 20:06:15 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_signal	g_variable;

void	t(char *line)
{
	char	**strs;

	strs = ft_split(line, ' ');
	if (!ft_strncmp(strs[0], "exit", 5))
		ft_exit(strs);
}

int	input(void)
{
	char	*line;

	line = NULL;
	while (1)
	{
		g_variable.input_mode = COMMAND_LINE;
		line = readline("minishell$ ");
		if (line == NULL)
		{
			free(line);
			break ;
		}
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		// t(line);
		printf("%s\n", line);
		add_history(line);
		free(line);
	}
	printf("exit\n");
	return (0);
}
