/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:46:29 by okaname           #+#    #+#             */
/*   Updated: 2025/03/24 20:53:50 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	ft_export(t_mini *mini)
{
	char	*path;

	path = getenv("");
	if (path != NULL)
	{
		printf(": %s\n", path);
	}
	else
	{
		print_sorted_env(mini->var_env);
	}
	free(path);
	return (0);
}
// int	main(int argc, char *argv[], char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	for (int i = 0; env[i] != NULL; i++)
// 	{
// 		printf("%s\n", env[i]);
// 	}
// 	return (0);
// }
