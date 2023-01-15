/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:14:42 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/26 20:22:27 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_name(char *argv)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(argv[0]) || argv[0] == '_'))
		return (false);
	while (argv[i] != '\0')
	{
		if (!(ft_isalnum(argv[i]) || argv[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}

void	remove_arg(t_env_list *prev, t_env_list *env)
{
	if (env == data()->env_list)
	{
		data()->env_list = env->next;
		free(env);
		env = data()->env_list;
		prev = env;
	}
	else
	{
		prev->next = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = prev->next;
	}
}

void	ft_unset_singal(char **argv, t_env_list *prev, t_env_list *env, int i)
{
	while (env != NULL)
	{
		if (ft_strcmp(argv[i], env->name) == 0)
		{
			remove_arg(prev, env);
			break ;
		}
		else
		{
			prev = env;
			env = env->next;
		}
	}
}

int	ft_unset(char *argv[])
{
	t_env_list	*prev;
	t_env_list	*tmp_env;
	int			i;

	i = 1;
	while (argv[i])
	{
		tmp_env = data()->env_list;
		prev = tmp_env;
		if (ft_strcmp(argv[i], " ") && !is_valid_name(argv[i]))
		{
			err_handle(2, "unset: ", argv[i]);
			data()->exit_state = 1;
		}
		ft_unset_singal(argv, prev, tmp_env, i);
		i++;
	}
	return (data()->exit_state);
}
