/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:15:28 by okaname           #+#    #+#             */
/*   Updated: 2025/05/04 18:16:38 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../analysis/lexer/lexer.h"
# include "../error/error.h"
# include "../struct.h"
# include "../utils/utils.h"
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

int		ft_cd(t_mini *mini, int count);
int		ft_echo(t_mini *mini, int count);
int		ft_env(t_mini *mini, int count);
int		ft_exit(t_mini *mini, int count);
int		ft_export(t_mini *mini, int count);
int		remake_env(t_env **env, char *s);
int		ft_pwd(t_mini *mini, int count);
int		ft_unset(t_mini *mini, int count);
int		print_sorted_env(t_env *head);
void	print_list(t_env *head);
int		count_array(char **array);

#endif