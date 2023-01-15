/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:46:40 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/26 20:22:08 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env_list(t_env_list **tmp_env)
{
	data()->env_list = malloc(sizeof(t_env_list));
	if (!data()->env_list)
		return (1);
	*tmp_env = data()->env_list;
	return (0);
}

void	init_env(char **envp)
{	
	char		**split;
	t_env_list	*tmp_env;

	if (init_env_list(&tmp_env))
		return ;
	if (!*envp)
		envp = ft_split("PATH=/", ':');
	while (*envp)
	{
		split = ft_split(*envp, '=');
		tmp_env->value = split[1];
		tmp_env->name = split[0];
		tmp_env->is_env = true;
		tmp_env->next = malloc(sizeof(t_env_list));
		if (!tmp_env->next)
			return ;
		if (*(envp + 1) == NULL)
			tmp_env->next = NULL;
		else
			tmp_env = tmp_env->next;
		envp++;
	}
}

static void	order_env(char ***env)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while ((*env)[i])
	{
		j = 0;
		while ((*env)[j])
		{
			if (ft_strcmp((*env)[i], (*env)[j]) < 0)
			{
				tmp = (*env)[i];
				(*env)[i] = (*env)[j];
				(*env)[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_env_or_export(char *cmd, char **env_arr)
{
	t_env_list	*tmp_env;

	tmp_env = data()->env_list;
	if (ft_strcmp(cmd, "env") == 0)
	{
		while (tmp_env != NULL)
		{
			if (tmp_env->is_env)
				printf("%s=%s\n", tmp_env->name, tmp_env->value);
			tmp_env = tmp_env->next;
		}
	}
	else
	{
		order_env(&env_arr);
		while (*env_arr)
		{
			printf("declare -x %s\n", *env_arr);
			env_arr++;
		}
	}
}

t_env_list	*ft_getenv_list(char *name)
{
	t_env_list	*tmp_env;

	tmp_env = data()->env_list;
	while (tmp_env != NULL)
	{
		if ((ft_strcmp(name, tmp_env->name)) == 0)
			return (tmp_env);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}
