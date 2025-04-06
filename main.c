/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:20:53 by okaname           #+#    #+#             */
/*   Updated: 2025/04/06 17:50:21 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_variable;

int	main(int argc, char *argv[], char **envp)
{
	t_mini	minishell;

	(void)argc;
	(void)argv;
	minishell.var_env = env_init(envp);
	set_act();
	input(&minishell);
	free_list(minishell.var_env);
	return (0);
}

// const char	*token_types[] = {"TOK_WORD", "TOK_BUILTIN", "TOK_PIPE",
// 		"TOK_REDIR_IN", "TOK_REDIR_OUT", "TOK_REDIR_APPEND", "TOK_HEREDOC",
// 		"TOK_SQUOTE_START", "TOK_SQUOTE_IN", "TOK_SQUOTE_END",
// 		"TOK_DQUOTE_START", "TOK_DQUOTE_IN", "TOK_DQUOTE_END", "TOK_BACKSLASH",
// 		"TOK_ENV_VAR", "TOK_ENV_VAR_NAME", "TOK_EXIT_STATUS", "TOK_NEWLINE",
// 		"TOK_NULL", "TOK_SPLIT", "UNSIGNED"};

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
// 		// printf("squote = %d : dquote = %d\n\n", token->squote,
// 		// token->dquote);
// 		i++;
// 	}
// }

// int	main(void)
// {
// 	char		*input;
// 	char		*line;
// 	int			fd;
// 	t_tokenset	*tokenset;

// 	fd = open("test.txt", O_RDONLY);
// 	input = NULL;
// 	while ((line = get_next_line(fd)))
// 	{
// 		input = ft_strjoin_gnl(input, line);
// 		if (!input)
// 			return (1);
// 		free(line);
// 	}
// 	tokenset = analysis(input);
// 	print_tokenset(tokenset);
// 	free_tokenset(tokenset);
// }
