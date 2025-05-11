/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:22:53 by yookamot          #+#    #+#             */
/*   Updated: 2025/05/11 15:48:40 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
valgrind --leak-check=full --show-leak-kinds=all
 --suppressions=suppression.txt ./minishell
*/

#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	t_mini	minishell;

	(void)argc;
	(void)argv;
	minishell.var_env = env_init(envp);
	minishell.exit_status = 0;
	input(&minishell);
	free_list(minishell.var_env);
	return (0);
}
