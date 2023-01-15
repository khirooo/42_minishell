/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:13:07 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/25 18:41:05 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

struct		s_env_list;
struct		s_token;

typedef struct s_args
{
	char			*value;
	int				space;
	struct s_args	*next;
}				t_args;

typedef struct s_infiles
{
	int					value;
	char				*dlmtr;
	struct s_infiles	*next;
}				t_infiles;

typedef struct s_outfiles
{
	int					value;
	struct s_outfiles	*next;
}				t_outfiles;

typedef struct s_heredocs
{
	int					value;
	struct s_heredocs	*next;
}				t_heredocs;

typedef struct s_simple_cmd
{
	char				*cmd;
	t_args				*args;
	t_infiles			*infile;
	t_outfiles			*outfile;
	t_heredocs			*heredocs;
	bool				error;
	int					err_code;
	struct s_simple_cmd	*next;
}				t_simple_cmd;

// functions in heredoc.c

char		*heredoc_expand(char *line);
int			read_heredocs(char	*dlmtr, int expantion);
int			add_infiles(t_infiles **infile, char *file, \
									int mode, int expantion);
int			add_outfiles(t_outfiles **outfile, char *file, int mode);

// functions in parser.c

bool		is_io_mod(int type);
int			init_cmd_struct(t_simple_cmd **simple_cmd);
int			add_args(t_args **args, char *value, int space);
int			parse_redir(t_simple_cmd *cmd, t_token *token);
int			parse(void);
void		print_exit(void);

//functions in parser_utils_1.c

bool		is_io_mod(int type);
int			init_cmd_struct(t_simple_cmd **simple_cmd);
int			add_args(t_args **args, char *value, int space);
void		ft_handel_in(t_simple_cmd *cmd, t_token *token, int last_op);

#endif