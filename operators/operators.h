/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:38:22 by okaname           #+#    #+#             */
/*   Updated: 2025/05/04 21:43:22 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATORS_H
# define OPERATORS_H

# include "../analysis/lexer/lexer.h"
# include "../error/error.h"
# include "../free/free.h"
# include "../struct.h"
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
# define C_HERE_DOC 2
# define P_HERE_DOC 3

char	*get_full_path(char *cmd, char **envp);
void	redirector(t_command *cmd);
int		here_doc(char *char_EOF, int *fd, t_mini *mini, t_tokenset *tokenset);
char	**list_to_char(t_env *env);

#endif