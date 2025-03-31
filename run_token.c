/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:37:03 by okaname           #+#    #+#             */
/*   Updated: 2025/04/01 05:55:14 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char			*token_types[] = {"TOK_WORD", "TOK_ASSIGNMENT",
				"TOK_LITERAL", "TOK_BUILTIN", "TOK_PIPE", "TOK_SEMICOLON",
				"TOK_AMPERSAND", "TOK_REDIR_IN", "TOK_REDIR_OUT",
				"TOK_REDIR_APPEND", "TOK_HEREDOC", "TOK_SQUOTE_START",
				"TOK_SQUOTE_IN", "TOK_SQUOTE_END", "TOK_DQUOTE_START",
				"TOK_DQUOTE_IN", "TOK_DQUOTE_END", "TOK_BACKSLASH",
				"TOK_LPAREN", "TOK_RPAREN", "TOK_ENV_VAR", "TOK_ENV_VAR_NAME",
				"TOK_EXIT_STATUS", "TOK_NEWLINE", "TOK_NULL", "TOK_EOF",
				"TOK_SPLIT", "UNSIGNED"};

void	print_tokenset(t_tokenset *tokenset)
{
	int		i;
	t_token	*token;

	i = 0;
	while (i < tokenset->count)
	{
		token = tokenset->token[i];
		if (!ft_strcmp(token->value, "\n"))
			printf("%-20s \\n           \n", token_types[token->type]);
		else
			printf("%-20s %-12s\n", token_types[token->type], token->value);
		i++;
	}
}

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

static t_command	**token_to_cmd(t_token **token, char **envp)
{
	int			cmd_count;
	t_command	**cmd;
	int			i;

	cmd_count = count_pipe(token) + 1;
	cmd = (t_command **)malloc(sizeof(t_command *) * (cmd_count + 1));
	if (cmd == NULL)
		error_malloc(NULL, NULL);
	i = 0;
	while (i < cmd_count)
	{
		cmd[i] = (t_command *)malloc(sizeof(t_command));
		cmd[i]->envp = envp;
		i++;
	}
	cmd[cmd_count] = NULL;
	set_fd_in(cmd, token);
	set_fd_out(cmd, token);
	set_cmd(cmd, token);
	if (cmd_count > 1)
		conect_pipe(cmd);
	return (cmd);
}

void	print_cmd(t_command **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i] != NULL)
	{
		printf("cmd[%d]->fd_in = %d\n", i, (cmd[i])->fd_in);
		printf("cmd[%d]->fd_out = %d\n", i, (cmd[i])->fd_out);
		j = 0;
		while (cmd[i]->cmd[j] != NULL)
		{
			printf("cmd[%d]->cmd[%d] = %s\n", i, j, cmd[i]->cmd[j]);
			j++;
		}
		i++;
	}
}

int	run_token(t_mini *minishell)
{
	t_tokenset	*tokenlist;
	int			i;

	i = 0;
	tokenlist = analysis(minishell->input);
	// print_tokenset(tokenlist);
	minishell->cmd = token_to_cmd(tokenlist->token,
			list_to_char(minishell->var_env));
	// print_cmd(minishell->cmd);
	while ((minishell->cmd)[i] != NULL)
	{
		redirector((minishell->cmd)[i]);
		i++;
	}
	return (0);
}
