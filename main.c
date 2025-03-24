/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:20:53 by okaname           #+#    #+#             */
/*   Updated: 2025/03/24 20:46:52 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_variable;

// int	main(int argc, char *argv[], char *envp[])
// {
// 	t_mini		minishell;
// 	t_command	cmd;

// 	(void)argc;
// 	(void)argv;
// 	minishell.var_env = env_init(envp);
// 	set_act();
// 	cmd.cmd = ft_split(argv[1], ' ');
// 	cmd.fd_in = here_doc(argv[2]);
// 	cmd.fd_out = 1;
// 	cmd.fd_err = open("error.txt", O_RDWR);
// 	cmd.envp = envp;
// 	redirector(&cmd);
// 	return (0);
// }

int	main(int argc, char *argv[], char **envp)
{
	t_mini	minishell;

	(void)argc;
	(void)argv;
	minishell.var_env = env_init(envp);
	set_act();
	input();
	return (0);
}
