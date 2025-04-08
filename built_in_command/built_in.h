/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:15:28 by okaname           #+#    #+#             */
/*   Updated: 2025/04/08 21:48:32 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../utils/utils.h"
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_command
{
	char			*cmd_path;
	char			**cmd;
	int				fd_in;
	int				fd_out;
	char			**envp;
	bool			built_in;
}					t_command;

typedef struct s_mini
{
	t_env			*var_env;
	t_command		**cmd;
	int				exit_status;
	char			*input;
	int				origin_fd_in;
	int				origin_fd_out;
}					t_mini;

int					ft_cd(t_mini *mini, int count);
int					ft_echo(t_mini *mini, int count);
int					ft_env(t_mini *mini, int count);
int					ft_exit(t_mini *mini, int count);
int					ft_export(t_mini *mini, int count);
int					ft_pwd(t_mini *mini, int count);
int					ft_unset(t_mini *mini, int count);
void				print_sorted_env(t_env *head);
void				print_list(t_env *head);
int					count_array(char **array);

#endif