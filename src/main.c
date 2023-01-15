/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:36:34 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/30 20:21:20 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(void)
{
	char	*line;

	usleep(900);
	if (isatty(fileno(stdin)))
		line = readline("minishell$ ");
	else
	{
		line = get_next_line(fileno(stdin));
		line = ft_strtrim(line, "\n", 1);
	}
	return (line);
}

int	end_session(void)
{
	rl_clear_history();
	print_exit();
	free_env(data()->env_list);
	return (data()->exit_state);
}

int	refresh_session(char *envp[])
{
	if (!*envp)
		*envp = ("PATH=/");
	data()->envp = envp;
	data()->state = 0;
	data()->tokens = NULL;
	data()->cmds = NULL;
	data()->n_heredocs = 0;
	return (0);
}

int	init_session(char *envp[])
{
	data()->exit_state = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
	init_env(envp);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	input = NULL;
	init_session(envp);
	if (argc > 1)
		printf("%s ... are ignored\n", argv[1]);
	while (true)
	{
		refresh_session(envp);
		input = prompt();
		if (input)
		{
			if (*input && ft_strlen(input) > 1)
				add_history(input);
			if (lexer(ft_strdup(input)) != 6 && !parse())
				xecute();
			free_tokens(data()->tokens);
			free_cmds(data()->cmds);
		}
		else
			break ;
		free(input);
	}
	return (end_session());
}
