/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 01:12:53 by okaname           #+#    #+#             */
/*   Updated: 2025/05/24 00:07:45 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	in(int *count, int *pipecount, char **cmd, int swich)
{
	if (swich == 1)
	{
		*count = 0;
		(*pipecount)++;
	}
	if (swich == 2)
	{
		*count = 0;
		*cmd = NULL;
	}
}

static void	cmd_count(t_command **cmd, t_token **token, t_mini *mini,
		t_tokenset *tokenset)
{
	int	i;
	int	count;
	int	pipe_count;

	i = -1;
	count = 0;
	pipe_count = 0;
	while (1)
	{
		if ((token[++i])->type == TOK_PIPE || (token[i])->type == TOK_NULL)
		{
			cmd[pipe_count]->cmd = malloc(sizeof(char *) * (count + 1));
			if (cmd[pipe_count]->cmd == NULL)
				error_malloc1(mini, tokenset);
			in(&count, &i, &cmd[pipe_count++]->cmd[count], 2);
			if ((token[i])->type == TOK_NULL)
				break ;
		}
		else if ((token[i])->type == 5 || (token[i])->type == 3
			|| (token[i])->type == 4 || (token[i])->type == 6)
			i++;
		else if ((token[i])->type == 0 || (token[i])->type == 11
			|| (token[i])->type == 8 || (token[i])->type == 1)
			count++;
	}
}

static void	set_here_doc(t_command **cmd, t_token **token, t_mini *mini,
		t_tokenset *tokenset)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = 0;
	while ((token[i])->value != NULL)
	{
		if ((token[i])->type == TOK_PIPE)
			pipe_count++;
		else if ((token[i])->type == TOK_HEREDOC)
		{
			if ((token[i + 1])->type == 8 || (token[i + 1])->type == 11)
				mini->expand_flag = 0;
			else
				mini->expand_flag = 1;
			here_doc((token[i + 1])->value, &(cmd[pipe_count]->fd_in), mini,
				tokenset);
		}
		if (mini->exit_status > 0)
			return ;
		i++;
	}
}

static char	*ft_strdup_error(char *s, t_mini *mini, t_tokenset *tokenset)
{
	char	*result;

	result = ft_strdup(s);
	if (result == NULL)
		error_malloc1(mini, tokenset);
	return (result);
}

void	set_cmd(t_command **cmd, t_token **token, t_mini *mini,
		t_tokenset *tokenset)
{
	int	i;
	int	pipe_count;
	int	count;

	i = -1;
	pipe_count = 0;
	count = 0;
	cmd_count(cmd, token, mini, tokenset);
	set_here_doc(cmd, token, mini, tokenset);
	while ((token[++i])->value != NULL)
	{
		if ((token[i])->type == TOK_PIPE)
			in(&count, &pipe_count, &mini->input, 1);
		else if ((token[i])->type == 5 || (token[i])->type == 3
			|| (token[i])->type == 4 || (token[i])->type == 6)
			i++;
		else if ((token[i])->type == 0 || (token[i])->type == 11
			|| (token[i])->type == 8 || (token[i])->type == 1)
		{
			if ((token[i])->type == TOK_BUILTIN && count == 0)
				cmd[pipe_count]->built_in = 1;
			cmd[pipe_count]->cmd[count++] = ft_strdup_error(token[i]->value,
					mini, tokenset);
		}
	}
}
