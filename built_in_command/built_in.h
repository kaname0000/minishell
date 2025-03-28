/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:15:28 by okaname           #+#    #+#             */
/*   Updated: 2025/03/26 01:17:47 by yookamot         ###   ########.fr       */
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

typedef struct s_mini
{
	t_env			*var_env;
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