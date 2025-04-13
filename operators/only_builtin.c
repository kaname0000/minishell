/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:10:01 by okaname           #+#    #+#             */
/*   Updated: 2025/04/13 16:47:14 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	reset_stdio(int *fd_stdin, int *fd_stdout)
{
	if (dup2(*fd_stdin, STDIN_FILENO) == -1)
		error_redirect();
	if (*fd_stdin != STDIN_FILENO && close(*fd_stdin) == -1)
		error_close();
	if (dup2(*fd_stdout, STDOUT_FILENO) == -1)
		error_redirect();
	if (*fd_stdout != 1 && close(*fd_stdout) == -1)
		error_close();
}

static void	redirct_stdio(int *fd_stdin, int *fd_stdout, int *fd_in,
		int *fd_out)
{
	*fd_stdin = dup(STDIN_FILENO);
	*fd_stdout = dup(STDOUT_FILENO);
	if (*fd_stdin == -1 || *fd_stdout == -1)
		error_redirect();
	if (dup2(*fd_in, STDIN_FILENO) == -1)
		error_redirect();
	if (*fd_in != STDIN_FILENO && close(*fd_in) == -1)
		error_close();
	if (dup2(*fd_out, STDOUT_FILENO) == -1)
		error_redirect();
	if (*fd_out != 1 && close(*fd_out) == -1)
		error_close();
}

int	run_cmd(t_mini *mini, int count)
{
	if (!ft_strncmp(mini->cmd[count]->cmd[0], "cd", 2))
		return (ft_cd(mini, count));
	else if (!ft_strncmp(mini->cmd[count]->cmd[0], "echo", 4))
		return (ft_echo(mini, count));
	else if (!ft_strncmp(mini->cmd[count]->cmd[0], "env", 3))
		return (ft_env(mini, count));
	else if (!ft_strncmp(mini->cmd[count]->cmd[0], "exit", 4))
		return (ft_exit(mini, count));
	else if (!ft_strncmp(mini->cmd[count]->cmd[0], "export", 6))
		return (ft_export(mini, count));
	else if (!ft_strncmp(mini->cmd[count]->cmd[0], "pwd", 3))
		return (ft_pwd(mini, count));
	else if (!ft_strncmp(mini->cmd[count]->cmd[0], "unset", 5))
		return (ft_unset(mini, count));
	return (1);
}

int	only_built_in(t_mini *mini, t_token **token)
{
	int	fd_stdin;
	int	fd_stdout;

	fd_stdin = 0;
	fd_stdout = 0;
	if (set_fd_b(mini->cmd[0], token) == 1)
		return (1);
	redirct_stdio(&fd_stdin, &fd_stdout, &mini->cmd[0]->fd_in,
		&mini->cmd[0]->fd_in);
	mini->cmd[0]->envp = list_to_char(mini->var_env);
	run_cmd(mini, 0);
	free_array(mini->cmd[0]->envp);
	free_array(mini->cmd[0]->cmd);
	free(mini->cmd);
	reset_stdio(&fd_stdin, &fd_stdout);
	return (0);
}
