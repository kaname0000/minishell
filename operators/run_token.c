/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:18:48 by okaname           #+#    #+#             */
/*   Updated: 2025/05/04 21:44:04 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../analysis/analysis.h"
#include "../error/error.h"
#include "../minishell.h"

static int	count_pipe(t_token **token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while ((token[i])->value != NULL)
	{
		if (token[i]->type == TOK_PIPE)
			count++;
		i++;
	}
	return (count);
}

static t_command	**token_to_cmd(t_tokenset *tokenset, t_mini *mini)
{
	int			cmd_count;
	t_command	**cmd;
	int			i;

	cmd_count = count_pipe(tokenset->token) + 1;
	cmd = (t_command **)malloc(sizeof(t_command *) * (cmd_count + 1));
	if (cmd == NULL)
		error_malloc1(mini, tokenset);
	i = 0;
	while (i < cmd_count)
	{
		cmd[i] = (t_command *)malloc(sizeof(t_command));
		if (cmd[i] == NULL)
			error_malloc1(mini, tokenset);
		cmd[i]->fd_in = 0;
		cmd[i]->fd_out = 1;
		cmd[i]->built_in = 0;
		cmd[i]->cmd = NULL;
		i++;
	}
	cmd[cmd_count] = NULL;
	set_cmd(cmd, tokenset->token, mini, tokenset);
	if (cmd_count > 1)
		conect_pipe(cmd, mini, tokenset);
	return (cmd);
}

static void	free_pid(int *pid, int count, int *status)
{
	int	i;
	int	s;

	i = 0;
	while (i < count)
	{
		waitpid(pid[i], &s, 0);
		*status = WEXITSTATUS(s);
		i++;
	}
	free(pid);
}

int	run_token(t_mini *mini)
{
	t_tokenset	*tokenset;
	int			i;
	int			count;
	int			pid_count;

	i = 0;
	count = 0;
	tokenset = analysis(mini->input, mini);
	pid_count = count_pipe(tokenset->token) + 1;
	mini->cmd = token_to_cmd(tokenset, mini);
	if (mini->exit_status == 130)
		return (free_cmd(mini->cmd), 0);
	mini->pid = malloc(sizeof(int) * pid_count);
	if (mini->pid == NULL)
		error_malloc1(mini, tokenset);
	while (1)
	{
		if (tokenset->token[i]->type == TOK_PIPE)
			make_prosses(mini, tokenset, count++, &mini->pid);
		else if (tokenset->token[i]->type == TOK_NULL)
		{
			if (count == 0 && mini->cmd[0]->built_in)
				mini->exit_status = only_built_in(mini, tokenset->token);
			else
				make_prosses(mini, tokenset, count, &mini->pid);
			break ;
		}
		i++;
	}
	free_pid(mini->pid, pid_count, &mini->exit_status);
	free_cmd(mini->cmd);
	// free_tokenset(tokenset, 1);
	return (0);
}
