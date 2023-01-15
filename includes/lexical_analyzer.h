/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:05:41 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/30 20:20:00 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICAL_ANALYZER_H
# define LEXICAL_ANALYZER_H

# include "minishell.h"

typedef struct s_token
{
	char			*value;
	int				type;
	bool			split;
	bool			error;
	bool			expansion;
	int				quot;
	int				err_code;
	struct s_token	*next;
}					t_token;

enum e_STN
{
	NEWLINE='\n',
	TAB='\t'
};

enum e_OPERATORS
{
	PIPE='|',
	EQUAL='=',
	LESS='<',
	GREATER='>',
	LESS_LESS=20000,
	GREATER_GREATER=40000
};

enum e_grammer
{
	WORD=-1,
	REDIR=20200,
	QMARK='?'
};

enum e_TOKENS
{
	TOKEN=-2,
	OPERATOR=-3,
	REDIR_IO=-2,
	DQUOTE='\"',
	SQUOTE='\'',
	FLAG='-',
	ERROR=-9,
	DOLLAR='$'
};

enum e_state
{
	INSQUOTE,
	OUTSQUOTE,
	INDQUOTE,
	OUTDQUOTE
};
void			get_user_input(char **buffer);
// functions in syntax_checker.c

int				print_err(char *format, char *s1, char *s2, char *s3);
int				err_handle(int error_code, char *prog, char *error_input);
int				check_syntax(void);
t_token			*get_next_token(t_token *token);
// functions in tokenize_operators.c

int				is_redir(t_token *token);
void			tokenize_operators(void);

// functions in param_expand.c

int				paramlen(char *param);
char			*field_split(char *str);
char			*expand_single(char *value, int var_pos, char *var);
void			replace_placeholders(void);
void			param_expand(void);

// functions in lexer.c

t_token			*init_t_token(void);
bool			quotes_matched(char *line);
void			fusion(void);
void			del_empty_tokens(void);
int				lexer(char *user_input);

// functions in tokenizer.c
int				set_state(char line);
bool			check_spaces(char c);
bool			check_operators(char c);
bool			shall_split(char *line, char *token_value, int state);
t_token			*get_tokens(char *input);

// functions in tokenizer_utils_1.c

char			*append_char_to_token(char *line, char c);
t_token			*save_token(char *line, char *value, int state);

// functions in tokenizer_utils_2.c

int				set_state(char line);
bool			check_spaces(char c);
bool			check_operators(char c);
int				is_space(char c);
int				ft_is_token_dlmtr(char c);

// functions in tokenizer_utils_3.c

t_token			*get_dq_token(char	**input, int *flag);
t_token			*get_sq_token(char	**input, int *flag);
t_token			*get_redir_token(char **input);

#endif