/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:15:28 by okaname           #+#    #+#             */
/*   Updated: 2025/04/04 21:18:42 by okaname          ###   ########.fr       */
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
	int				error_flag;
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

void				ft_exit(char **strs);
int					ft_pwd(void);
void				print_sorted_env(t_env *head);
void				print_list(t_env *head);
int					ft_pwd(void);
int					ft_echo(int nflag, char **strs, t_env *env);

#endif