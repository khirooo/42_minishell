/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:36:04 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/30 18:27:54 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include	<readline/readline.h>
# include	<readline/history.h>
# include	<stdio.h>
# include	<string.h>
# include	<signal.h>
# include	<stdbool.h>
# include	<unistd.h>
# include	"../ft_printf/includes/ft_printf.h"
# include	"get_next_line.h"
# include	"env.h"
# include	"lexical_analyzer.h"
# include	"parser.h"
# include	"execution.h"
# include	<termios.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<sys/wait.h>
# include	<limits.h>

struct	s_token;
struct	s_args;
struct	s_infiles;
struct	s_outfiles;
struct	s_heredocs;
struct	s_simple_cmd;

typedef struct s_env_list
{
	char				*name;
	char				*value;
	bool				is_env;
	struct s_env_list	*next;
}				t_env_list;

typedef struct s_data
{
	t_token				*tokens;
	t_env_list			*env_list;
	t_simple_cmd		*cmds;
	char				**envp;
	int					state;
	int					exit_state;
	int					n_heredocs;
}				t_data;

char		*ft_getenv(char *name);
t_data		*data(void);
t_env_list	*ft_getenv_list(char *name);
void		handler(int signum);
int			parser_helper(t_simple_cmd *simple_cmd, t_token *token);

// free functions

void		free_tokens(t_token	*tokens);
void		free_args(t_args *args);
void		free_infile(t_infiles *infile);
void		free_outfile(t_outfiles *outfile);
void		free_cmds(t_simple_cmd *cmd);
void		free_env(t_env_list *env_list);
void		free_all(void);
void		free_dp(char **i);
// functions in utils.c

char		ft_strcmp(const char *s1, const char *s2);

// functions in error_handler.c

int			print_err(char *format, char *s1, char *s2, char *s3);
int			err_handle_helper(int error_code, char *prog, \
								char *err_input, char *err[]);
int			err_handle(int error_code, char *prog, char *error_input);

// functions in free_utils_1.c

void		free_env(t_env_list *env_list);

#endif
