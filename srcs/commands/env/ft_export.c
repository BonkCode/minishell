/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:02:51 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/08 17:15:38 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/commands.h"

char		**clear_tokens(char **tokens, int count)
{
	int	i;

	i = -1;
	if (count < 0)
	{
		while (tokens[++i])
		{
			free(tokens[i]);
			tokens[i] = NULL;
		}
	}
	else
	{
		while (++i < count)
		{
			free(tokens[i]);
			tokens[i] = NULL;
		}
	}
	free(tokens);
	tokens = NULL;
	return (NULL);
}

int		check_var_in_env(t_list *env, char *var, char *arg)
{
	char	**split_res;

	while (env)
	{
		split_res = ft_split(env->content, '=');
		if (split_res)
		{
			if (ft_strncmp(split_res[0], var, ft_strlen(var) + 1) == 0)
			{
				free(env->content);
				env->content = NULL;
				env->content = ft_strdup(arg);
				clear_tokens(split_res, -1);
				return (1);
			}
		}
		env = env->next;
	}
	clear_tokens(split_res, -1);
	return (0);
}

void	add_var(void)
{
}

void	ft_export(t_list *env, char *arg)
{
	char **split_res;

	split_res = ft_split(arg, '=');
	if (check_var_in_env(env, split_res[0], arg))
	{
		clear_tokens(split_res, -1);
		return ;
	}
	/*
	while (env)
	{
		split_res = ft_split(env->content, '=');
		//printf("%s\n", env->content);
		if (ft_strncmp(split_res[0], arg, ft_strlen(arg) + 1) == 0)
		{
			env->content = ft_strjoin("Test", "=");
			break ;
		}
		env = env->next;
	}
	*/
	add_var();
	//printf("end\n");
}
