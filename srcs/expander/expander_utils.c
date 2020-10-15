/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 17:01:34 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/15 16:42:10 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "m_types.h"
#include "flexer.h"

extern int	g_status;

static int		delete_qmarks(char **token)
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

static void		get_var_value(char *name, char **value, t_list *env)
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
	free_2_str(&env_value, &env_name);
}

static void		get_var_name(int flag, char **var_name, char **token, int *i)
{
	int	len;

	if ((*token)[*i + 1] == '?')
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

static void		change_value(char **token, t_var var, int i)
{
	char	*free_temp;
	char	*token_temp;

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

void			expand_token(char **token, t_list *env)
{
	t_var	var;
	int		i;
	int		flag;

	if ((flag = delete_qmarks(token)) == 1)
		return ;
	i = 0;
	while ((*token)[i])
	{
		if ((*token)[i] == '$' && (i == 0 || (*token)[i - 1] != '\\'))
		{
			get_var_name(flag, &var.name, token, &i);
			get_var_value(var.name, &var.value, env);
			var.value = var.value ? var.value : ft_strdup("");
			change_value(token, var, i);
			free_2_str(&var.value, &var.name);
			i = 0;
		}
		else
			++i;
	}
}
