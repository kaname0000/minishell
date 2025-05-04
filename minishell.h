/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:21:50 by okaname           #+#    #+#             */
/*   Updated: 2025/05/04 19:50:49 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "built_in_command/built_in.h"
# include "error/error.h"
# include "operators/operators.h"
# include "struct.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define REDIR_IN 1
# define REDIR_OUT 1
# define HERE_DOC 2
# define APPEND 2

int		input(t_mini *minishell);
void	set_act(void);
t_env	*env_init(char **env);
void	free_list(t_env *head);
int		run_token(t_mini *minishell);
void	conect_pipe(t_command **cmd, t_mini *mini, t_tokenset *tokenset);
void	set_cmd(t_command **cmd, t_token **token, t_mini *mini,
			t_tokenset *tokenset);
int		set_fd(t_command **cmd, t_token **token, int count);
int		set_fd_b(t_command *cmd, t_token **token);
void	make_prosses(t_mini *mini, t_tokenset *tokenlist, int count, int **pid);
void	built_in_prosses(t_mini *mini, int count);
int		run_cmd(t_mini *mini, int count);
int		only_built_in(t_mini *mini, t_token **token);

#endif
