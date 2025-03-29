/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:20:53 by okaname           #+#    #+#             */
/*   Updated: 2025/03/29 23:16:40 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_variable;

// int	main(int argc, char *argv[], char *envp[])
// {
// 	t_mini		minishell;
// 	t_command	cmd;

// 	(void)argc;
// 	(void)argv;
// 	minishell.var_env = env_init(envp);
// 	set_act();
// 	cmd.cmd = ft_split(argv[1], ' ');
// 	// cmd.fd_in = here_doc(argv[2]);
// 	cmd.fd_in = open_infile(argv[1]);
// 	cmd.fd_out = 1;
// 	cmd.fd_err = open("error.txt", O_RDWR);
// 	cmd.envp = envp;
// 	// redirector(&cmd);
// 	return (0);
// }

// int	main(int argc, char *argv[], char **envp)
// {
// 	t_mini	minishell;

// 	(void)argc;
// 	(void)argv;
// 	minishell.var_env = env_init(envp);
// 	set_act();
// 	// input();
// 	ft_echo(1, &argv[1], minishell.var_env);
// 	return (0);
// }

const char	*token_types[] = {"TOK_WORD", "TOK_ASSIGNMENT", "TOK_LITERAL",
		"TOK_BUILTIN", "TOK_PIPE", "TOK_SEMICOLON", "TOK_AMPERSAND",
		"TOK_REDIR_IN", "TOK_REDIR_OUT", "TOK_REDIR_APPEND", "TOK_HEREDOC",
		"TOK_SQUOTE_START", "TOK_SQUOTE_IN", "TOK_SQUOTE_END",
		"TOK_DQUOTE_START", "TOK_DQUOTE_IN", "TOK_DQUOTE_END", "TOK_BACKSLASH",
		"TOK_LPAREN", "TOK_RPAREN", "TOK_ENV_VAR", "TOK_ENV_VAR_NAME",
		"TOK_EXIT_STATUS", "TOK_NEWLINE", "TOK_NULL", "TOK_EOF", "TOK_SPLIT",
		"UNSIGNED"};

static void	print_tokenset(t_tokenset *tokenset)
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

int	main(void)
{
	char		*input;
	char		*line;
	int			fd;
	t_tokenset	*tokenset;

	fd = open("test.txt", O_RDONLY);
	input = NULL;
	while ((line = get_next_line(fd)))
	{
		input = ft_strjoin_gnl(input, line);
		if (!input)
			return (1);
		free(line);
	}
	tokenset = analysis(input);
	print_tokenset(tokenset);
	free_tokenset(tokenset);
}
