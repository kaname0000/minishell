/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:44:06 by yookamot          #+#    #+#             */
/*   Updated: 2024/12/14 18:26:08 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

pid_t	pipex_input(char **argv, char **envp, int *pipefd);
pid_t	pipex_output(pid_t pid1, char **argv, char **envp, int *pipefd);
int		open_and_redirect_in(char *infile);
void	open_and_redirect_out(pid_t pid1, char *outfile);
char	*get_full_path1(char *cmd, char **envp);
char	*get_full_path2(pid_t pid1, char *cmd, char **envp);
pid_t	return_pid1(char **argv, char *full_path, char **envp, int *pipefd);
pid_t	return_pid2(pid_t pid1, char **argv, char **envp, int *pipefd);
void	close_process(int *pipefd, pid_t pid1, pid_t pid2);

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

void	ft_free_split(char **arr);
char	*ft_strjoin_free(char *s1, char *s2);

#endif