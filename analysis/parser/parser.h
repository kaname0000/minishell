/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:37:21 by yookamot          #+#    #+#             */
/*   Updated: 2025/04/04 23:42:25 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../analysis.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_redir
{
	t_token_type type; // 入出力の種類（<, >, >>, <<）
	char *file;        // 対象ファイル名
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char **argv;        // コマンド + 引数（execveに渡せる形）
	t_redir *redir;     // リダイレクション情報のリスト
	int is_builtin;     // ビルトインフラグ
	struct s_cmd *next; // パイプでつながる次のコマンド
}					t_cmd;

void				first_check(t_tokenset *tokenset);
void				error_token(t_tokenset *tokenset, char *value);
void				error_end_of_file(t_tokenset *tokenset, char *value);

#endif