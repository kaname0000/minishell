/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:21:41 by okaname           #+#    #+#             */
/*   Updated: 2025/04/13 18:18:50 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "../struct.h"

void	free_array(char **array);
void	free_cmd(t_command **cmd);
void	free_list(t_env *head);
void	free_mini(t_mini *mini);

#endif