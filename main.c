/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:20:53 by okaname           #+#    #+#             */
/*   Updated: 2025/03/13 21:20:31 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_info	g_variable;

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;
	set_act();
	input();
	return (0);
}

// int	main(int argc, char *argv[], char **envp)
// {
// 	t_command	cmd;

// 	(void)argc;
// 	cmd.cmd = ft_split(argv[1], ' ');
// 	cmd.envp = envp;
// 	cmd.fd_in = open_infile(argv[2]);
// 	cmd.fd_out = open_outfile(argv[3]);
// 	if (cmd.fd_in == -1 || cmd.fd_out == -1)
// 		return (1);
// 	redirector(&cmd);
// 	ft_free_split(cmd.cmd);
// 	return (0);
// }