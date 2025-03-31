/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:38:22 by okaname           #+#    #+#             */
/*   Updated: 2025/04/01 04:47:40 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATORS_H
# define OPERATORS_H

# include "../built_in_command/built_in.h"
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

# define COMMAND_LINE 1
# define HERE_DOC 2

typedef struct s_signal
{
	int	input_mode;
}		t_signal;

char	*get_full_path(char *cmd, char **envp);
pid_t	redirector(t_command *cmd);
// pid_t		redirector(t_mini *minishell);
int		here_doc(char *char_EOF, int *last, int *fd);
char	**list_to_char(t_env *env);

#endif