/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:38:22 by okaname           #+#    #+#             */
/*   Updated: 2025/03/13 20:12:26 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATORS_H
# define OPERATORS_H

# include "../error/error.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_command
{
	char	*cmd_path;
	char	**cmd;
	int		fd_in;
	int		fd_out;
	char	**envp;
}			t_command;

int			open_outfile(char *outfile);
int			open_infile(char *infile);
int			open_appendfile(char *appendfile);
char		*get_full_path(char *cmd, char **envp);
pid_t		redirector(t_command *cmd);
int			here_doc(char *char_EOF);

#endif