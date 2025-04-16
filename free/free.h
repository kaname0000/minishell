/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:21:41 by okaname           #+#    #+#             */
/*   Updated: 2025/04/16 22:04:14 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "../analysis/lexer/lexer.h"
# include "../struct.h"

void	free_array(char **array);
void	free_cmd(t_command **cmd);
void	free_list(t_env *head);
void	free_mini(t_mini *mini);
void	free_tokenset(t_tokenset *tokenset, int key);

#endif