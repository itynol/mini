/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:06:35 by jterry            #+#    #+#             */
/*   Updated: 2019/05/08 21:38:30 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void		change_pwd(char **tmp_env, char **com)
{
	char	**tmp;
	int 	i;
	int		j;
	char	*str;
	int		len;

	j = -1;
	i = ft_getenv(tmp_env, "PWD", NULL);
	if (com[1][0] == '/')
	{
		free(tmp_env[i]);
		tmp_env[i] = ft_strrejoin("PWD=", com[1], 0);
		return ;
	}
	tmp = ft_strsplit(com[1], '/');
	while (tmp[++j])
	{
		if (tmp[j][0] == '.')
		{
			if (tmp[j][1] == '.')
			{
				len = ft_strlen(tmp_env[i]);
				str = tmp_env[i];
				while (str[len] != '/')
					len--;
				str[len] = '\0';
				free (tmp_env[i]);
				tmp_env[i] = ft_strdup(str);
				continue ;
			}
			else
				continue ;
		}
		tmp_env[i] = ft_strrejoin(tmp_env[i], "/", 1);
		tmp_env[i] = ft_strrejoin(tmp_env[i], tmp[j], 3);
	}
}

int			command_check(char ***tmp_env, char **command)
{
	if (ft_strcmp(command[0], "cd") == 0)
		cd_command(command, *tmp_env);
	else if (ft_strcmp(command[0], "env") == 0)
		env_command(*tmp_env);
	else if (ft_strcmp(command[0], "ls") == 0)
		ls_command(command);
	else if (ft_strcmp(command[0], "pwd") == 0)
		pwd_command(*tmp_env);
	else if (ft_strcmp(command[0], "echo") == 0)
		echo_command(command);
	else if (ft_strcmp(command[0], "setenv") == 0)
		setenv_command(tmp_env, command);
	else if (ft_strcmp(command[0], "unsetenv") == 0)
		unsetenv_command(tmp_env, command);
	else
		return (0);
	return (1);
}

void		ft_read(char **tmp_env, char *str, char **command)
{
	int		i;
	char	**commands;
	int		l;

	i = 0;
	while (1)
	{
		l = 0;
		str = readline("$>");
		if (!str || !(*str))
			continue ;
		add_history(str);
		commands = ft_strsplit(str, ';');
		while (commands[l])
		{
			command = ft_dollar(com, tmp_env);
			if (ft_strcmp(command[0], "exit") == 0)
				exit (0);
			i = command_check(&tmp_env, command);
			if (i == 0)
			{
				if (all_command(command) < 0)
				{
					write(2, "minishell: command not found: ", 30);
					ft_putstr(command[0]);
					write(2, "\n", 1);
					exit (0);
				}
			}
			free (command);
			l++;
		}
		free (commands);
	}
}

char		**ft_envcreat(char **env)
{
	char	**tmp;
	int		len_up;
	int		len;

	len_up = 0;
	len = 0;
	while (env[len_up])
		len_up++;
	tmp = malloc(sizeof(tmp) * len_up + 1);
	while (env[len])
	{
		tmp[len] = ft_strdup(env[len]);
		len++;
	}
	tmp[len_up] = "\0";
	return (tmp);
}

int			main(int ac, char **av, char **env)
{
	char	**tmp_env;

	ac = 0;
	av = NULL;
	tmp_env = ft_envcreat(env);
	ft_read(tmp_env, NULL, NULL);
	return (0);
}
