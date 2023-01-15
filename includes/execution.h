/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:49:03 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/30 18:37:51 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

enum e_exec_STATE
{
	IDLE = 0,
	EXEC = 1,
	HEREDOC = 2,
};

enum e_FILE_DESCRIPTORS
{
	STDIN_INIT = 0,
	STDOUT_INIT = 1,
	IN = 2,
	OUT = 3,
};

struct	s_token;
struct	s_args;
struct	s_infiles;
struct	s_outfiles;
struct	s_heredocs;
struct	s_simple_cmd;

int			xecute(void);
void		init_fds(int fd[4]);
void		reset_fds(int fd[4]);
char		**ft_getpath(char *cmd);
int			check_cmds(char	*cmd);
bool		is_builtin(char	*cmd);
bool		is_builtin2(char	*cmd);
int			add_env(char *name, char *value);
int			init_args(t_simple_cmd *simple_cmd, char ***arg_array, int mode);
t_token		*get_next_word(t_token *token);

/* ----- Inbuilts Commands */
int			ft_export(int argc, char *argv[]);
int			ft_env(int argc);
int			ft_unset(char *argv[]);
int			ft_cd(int argc, char **argv);
int			ft_pwd(void);
// int		ft_unset(int argc, char *argv[], char *envp[]);
int			ft_echo(int argc, char **argv);
int			ft_exit(int argc, char **argv);
int			exec_builtin1(t_simple_cmd *simple_cmd);
int			exec_builtin2(t_simple_cmd *simple_cmd);
int			child_process(t_simple_cmd *simple_cmd);

int			is_valid_name(char *argv);
char		**env_to_arr(void);
void		init_env(char **envp);
void		free_dp(char **i);

// functions in executer_cmd.c

int			get_infile(t_simple_cmd *simple_cmd, int fdin);
int			get_outfile(t_simple_cmd *simple_cmd, int fd[4]);
int			exec_cmd_helper(t_simple_cmd *simple_cmd, int fd[4], int *ret);
int			exec_cmd(t_simple_cmd *simple_cmd, int fd[4]);

#endif