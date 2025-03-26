/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:55:23 by okaname           #+#    #+#             */
/*   Updated: 2025/03/26 01:15:45 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "../utils/utils.h"
# include <errno.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

void	error_arg(void);
void	error_pipe(void);
void	error_infile_invalid(char *infile);
void	error_infile_open_failed(char *infile);
void	error_infile_close_failed(void);
void	error_redirect(void);
void	error_malloc(char **arr1, char **arr2);
void	error_command1(char **cmd_parts);
void	error_execve1(void);
void	error_fork1(void);
void	error_outfile_invalid(pid_t pid1, char *outfile);
void	error_outfile_open_failed(pid_t pid1, char *outfile);
void	error_outfile_close_failed(pid_t pid1);
void	error_command2(pid_t pid1, char **cmd_parts);
void	error_execve2(pid_t pid1, char *full_path, char **cmd_args);
void	error_fork2(pid_t pid1);
void	error_redirect_out(pid_t pid1);
void	error_command1_directory(char **cmd_parts);
void	error_command2_directory(pid_t pid1, char **cmd_parts);
void	error_command1_nonexistent(char **cmd_parts);
void	error_command2_nonexistent(pid_t pid1, char **cmd_parts);

#endif