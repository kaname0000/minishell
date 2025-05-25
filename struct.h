/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okaname <okaname@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:16:09 by okaname           #+#    #+#             */
/*   Updated: 2025/05/25 18:10:01 by okaname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "libft/libft.h"
# include <stdbool.h>

# define FAILED 0
# define SUCCESS 1

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_command
{
	char				*cmd_path;
	char				**cmd;
	int					fd_in;
	int					fd_out;
	char				**envp;
	bool				built_in;
	int					pid;
}						t_command;

enum					e_tokentype
{
	TOK_WORD,
	TOK_BUILTIN,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_REDIR_APPEND,
	TOK_HEREDOC,
	TOK_SQUOTE_START,
	TOK_SQUOTE_IN,
	TOK_SQUOTE_END,
	TOK_DQUOTE_START,
	TOK_DQUOTE_IN,
	TOK_DQUOTE_END,
	TOK_NEWLINE,
	TOK_NULL,
	TOK_SPLIT,
	UNSIGNED
};

typedef struct s_token
{
	enum e_tokentype	type;
	char				*value;
	int					squote;
	int					dquote;
	int					count;
	struct s_token		**split_token;
}						t_token;

typedef struct s_tokenlist
{
	t_token				***token;
	char				*input;
	int					set_count;
	int					*token_count;
	int					*sflag;
	int					*dflag;
}						t_tokenlist;

typedef struct s_tokenset
{
	t_token				**token;
	int					count;
	char				*input;
}						t_tokenset;

typedef struct s_signal
{
	int					signal;
}						t_signal;

typedef struct s_mini
{
	t_env				*var_env;
	t_command			**cmd;
	int					exit_status;
	char				*input;
	t_tokenset			*tokenset;
	int					expand_flag;
	int					line;
}						t_mini;

#endif