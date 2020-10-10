/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 17:01:34 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/10 18:12:48 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "m_types.h"
#include "flexer.h"

extern int	g_status;

int		delete_qmarks(char **token)
{
	char	*temp;
	int		flag;

	flag = -1;
	if ((*token)[0] == '\'' || (*token)[0] == '\"')
	{
		flag = (*token)[0] == '\'' ? 1 : 0;
		temp = *token;
		*token = ft_substr(*token, 1, ft_strlen(*token) - 2);
		free(temp);
	}
	return (flag);
}

void	get_var_value(char *name, char **value, t_list *env)
{
	char	*env_name;
	char	*env_value;

	*value = NULL;
	if (!ft_strncmp(name, "?", 2))
	{
		*value = ft_itoa(g_status);
		return ;
	}
	while (env)
	{
		env_name = ft_substr(env->content, 0,
				ft_strchr(env->content, '=') - (char*)env->content);
		env_value = ft_strdup(ft_strchr(env->content, '=') + 1);
		if (!ft_strncmp(name, env_name, ft_strlen(name) + 1))
		{
			*value = env_value;
			free(env_name);
			env_name = NULL;
			return ;
		}
		env = env->next;
	}
	free(env_name);
	env_name = NULL;
	free(env_value);
	env_value = NULL;
}

void	get_var_name(int flag, char **var_name, char **token, int *i)
{
	int	len;

	if (flag == -1)
		*var_name = ft_strdup(*token + 1);
	else if ((*token)[*i + 1] == '?')
	{
		*var_name = ft_strdup("?");
		*i += 2;
	}
	else
	{
		len = 0;
		while ((*token)[++(*i)])
		{
			if (!ft_isprint((*token)[*i]))
				break ;
			if (!ft_isalnum((*token)[*i]) && (*token)[*i] != '_')
				break ;
			++len;
		}
		if (len == 0)
			return ;
		*var_name = malloc(len + 1);
		ft_strlcpy(*var_name, *token + (*i) - len, len + 1);
	}
}

void	change_value(char *token_temp, char **token, t_var var, int i)
{
	char	*free_temp;

	token_temp = ft_substr(*token, 0, ft_strchr(*token, '$') - *token);
	token_temp = ft_strjoin_gnl(token_temp, var.value);
	free_temp = ft_substr(*token, i, ft_strlen(*token + i));
	token_temp = ft_strjoin_gnl(token_temp, free_temp);
	free(free_temp);
	free(*token);
	free_temp = NULL;
	var.value = NULL;
	*token = token_temp;
}

void	expand_token(char **token, t_list *env)
{
	t_var	var;
	int		i;
	char	*token_temp;
	int		flag;

	if ((flag = delete_qmarks(token)) == 1)
		return ;
	i = -1;
	while ((*token)[++i])
	{
		if ((*token)[i] == '$' && (i == 0 || (*token)[i - 1] != '\\'))
		{
			get_var_name(flag, &var.name, token, &i);
			get_var_value(var.name, &var.value, env);
			var.value = var.value ? var.value : ft_strdup("");
			if (flag == -1)
			{
				token_temp = *token;
				*token = var.value;
				free(token_temp);
				return ;
			}
			change_value(token_temp = NULL, token, var, i);
			if (var.name)
				free(var.name);
			if (var.value)
				free(var.value);
			var.value = NULL;
			var.name = NULL;
			i = -1;
		}
	}
}
