/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:16:09 by okaname           #+#    #+#             */
/*   Updated: 2025/04/16 21:59:42 by yookamot         ###   ########.fr       */
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
}						t_command;

typedef struct s_mini
{
	t_env				*var_env;
	t_command			**cmd;
	int					exit_status;
	char				*input;
	int					origin_fd_in;
	int					origin_fd_out;
	int					*pid;
}						t_mini;

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
	int					is_complete;
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
	int					input_mode;
}						t_signal;

#endif