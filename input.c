/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:17:08 by okaname           #+#    #+#             */
/*   Updated: 2025/03/13 21:23:13 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		t(line);
		add_history(line);
		free(line);
	}
	printf("exit\n");
	return (0);
}
