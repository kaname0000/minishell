/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:15:28 by okaname           #+#    #+#             */
/*   Updated: 2025/04/16 19:14:47 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../analysis/lexer/lexer.h"
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
int		ft_pwd(t_mini *mini, int count);
int		ft_unset(t_mini *mini, int count);
void	print_sorted_env(t_env *head);
void	print_list(t_env *head);
int		count_array(char **array);

#endif