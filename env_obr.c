/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_obr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:19:17 by jterry            #+#    #+#             */
/*   Updated: 2019/05/09 05:20:38 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**ft_envadd(char **env, int flag, int pos)
{
	char	**tmp;
	int		len_up;
	int		len;

	len_up = 0;
	len = 0;
	while (env[len_up])
		len_up++;
	tmp = malloc(sizeof(tmp) * (len_up + flag + 1));
	len_up = 0;
	while (env[len][0] != '\0')
	{
		if (len == pos)
		{
			len++;
			continue ;
		}
		tmp[len_up] = env[len];
		len_up++;
		len++;
	}
	if (flag > 0)
		tmp[len] = ft_strnew(0);
	tmp[len + flag] = "\0";
	return (tmp);
}

char		**ft_setenv(char **tmp_env, char *str, char *buf)
{
	int		i;
	char	**tmp;
	
	i = 0;
	if ((i = ft_getenv(tmp_env, str, NULL)) > 0)
	{
		free(tmp_env[i]);
		tmp_env[i] = ft_strrejoin(str, "=", 0);
		tmp_env[i] = ft_strrejoin(tmp_env[i], buf, 1);
		return (tmp_env);
	}
	else
	{
		i = 0;
		tmp = ft_envadd(tmp_env, 1, 0);
		while (tmp[i] != '\0')
			i++;
		tmp[i] = ft_strrejoin(str, "=", 1);
		tmp[i] = ft_strrejoin(tmp[i], buf, 3);
		return (tmp);
	}
}

int			ft_getenv(char **tmp_env, char *str, char **buf)
{
	char	**tmp;
	int		i;
	int		j;
	
	i = 0;
	j = 0;

	while(tmp_env[i][0] != '\0')
	{
		tmp = ft_strsplit(tmp_env[i], '=');
		if (ft_strcmp(tmp[0], str) == 0)
		{	
			while (tmp_env[i][j] != '=')
				j++;
			if (buf)
				*buf = &tmp_env[i][j + 1];
			free (tmp);
			return (i);
		}
		free (tmp);
		i++;
	}
	return (-1);
}

void		unsetenv_command(char ***tmp_env, char **command)
{
	int		i;
	int		l;

	l = 0;
	while (command[++l])
	{
		if ((i = ft_getenv(*tmp_env, command[l], NULL)) < 0)
			continue ;
		*tmp_env = ft_envadd(*tmp_env, -1, i);
	}
}

void		setenv_command(char ***tmp_env, char **command)
{
	char	**tr;
	int		i;

	i = 0;
	while (command[++i])
	{
		tr = ft_strsplit(command[i], '=');
		if (!tr[1])
			continue ;
		*tmp_env = ft_setenv(*tmp_env, tr[0], tr[1]);
		free (tr);
	}
}
