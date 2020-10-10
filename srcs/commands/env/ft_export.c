/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:02:51 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/10 16:44:06 by rvernius         ###   ########.fr       */
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

int			check_var_in_env(t_list *env, char *var, char *arg)
{
	char	**split_res;

	while (env)
	{
		split_res = ft_split(env->content, '=');
		if (split_res)
		{
			if (ft_strncmp(split_res[0], var, ft_strlen(var) + 1) == 0)
			{
				//printf("%s\n", env->content);
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

void		add_env_var(t_list *env, char *arg)
{
	t_list *new_var;

	while (env->next->next)
	{
		env = env->next;
	}
	new_var = ft_lstnew(arg);
	new_var->next = env->next;
	env->next = new_var;
}

void		ft_export(t_list *env, char *arg)
{
	char **split_res;

	split_res = ft_split(arg, '=');
	if (check_var_in_env(env, split_res[0], arg))
	{
		clear_tokens(split_res, -1);
		return ;
	}
	add_env_var(env, arg);
	clear_tokens(split_res, -1);
}
