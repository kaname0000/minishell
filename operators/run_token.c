
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:37:03 by okaname           #+#    #+#             */
/*   Updated: 2025/04/16 21:23:28 by okaname          ###   ########.fr       */
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

// const char			*token_types[] = {"TOK_WORD", "TOK_BUILTIN", "TOK_PIPE",
// 				"TOK_REDIR_IN", "TOK_REDIR_OUT", "TOK_REDIR_APPEND",
// 				"TOK_HEREDOC", "TOK_SQUOTE_START", "TOK_SQUOTE_IN",
// 				"TOK_SQUOTE_END", "TOK_DQUOTE_START", "TOK_DQUOTE_IN",
// 				"TOK_DQUOTE_END", "TOK_NEWLINE", "TOK_NULL", "TOK_SPLIT",
// 				"UNSIGNED"};

// static void	print_tokenset(t_tokenset *tokenset)
// {
// 	int		i;
// 	t_token	*token;

// 	i = 0;
// 	while (i < tokenset->count)
// 	{
// 		token = tokenset->token[i];
// 		if (!ft_strcmp(token->value, "\n"))
// 			printf("%-20s \\n           \n", token_types[token->type]);
// 		else
// 			printf("%-20s %-12s\n", token_types[token->type], token->value);
// 		i++;
// 	}
// }

static void	free_pid(int *pid, int count, int *status)
{
	int	i;

	i = 0;
	while (i < count)
	{
		waitpid(pid[i], status, 0);
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
	mini->pid = malloc(sizeof(int) * pid_count);
	if (mini->pid == NULL)
		error_malloc1(mini, tokenset);
	// print_tokenset(tokenset);
	mini->cmd = token_to_cmd(tokenset, mini);
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
	return (0);
}
