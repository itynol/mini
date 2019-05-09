/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:20:43 by jterry            #+#    #+#             */
/*   Updated: 2019/05/09 03:36:44 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		change_pass(char **tmp_env)
{
	char **tmp;
	char *tmp_pwd;

	tmp = ft_strsplit(tmp_env[ft_getenv(tmp_env, "OLDPWD", NULL)], '=');
	ft_getenv(tmp_env, "PWD", &tmp_pwd);
	tmp_env = ft_setenv(tmp_env, "OLDPWD", tmp_pwd);
	change_pwd(tmp_env, tmp);
}

void		cd_command(char **command, char **tmp_env)
{
	char	*buf;
	char	**tmp;


	if (!(ft_strcmp(command[1], "-")) && !(command[2]))
	{
		change_pass(tmp_env);
		return ;
	}
	ft_getenv(tmp_env, "PWD", &buf);
	ft_setenv(tmp_env, "OLDPWD", buf);
	if (!(command[1]))
	{
		tmp = malloc(sizeof(tmp));
		ft_getenv(tmp_env, "HOME", &buf);
		chdir(buf);
		tmp[1] = buf;
		change_pwd(tmp_env, tmp);
		free (tmp);
	}
	else if (command[2])
	{
		write(2, "cd: string not in pwd: ", 23);
		ft_putstr(command[1]);
		write(2, "\n", 1);
	}
	else if (chdir(command[1]) < 0)
	{
		write(2, "cd: no such file or directory: ", 31);
		ft_putstr(command[1]);
		write(2, "\n", 1);
	}
	else
		change_pwd(tmp_env, command);

}

void		env_command(char **tmp_env)
{
	int i;

	i = 0;

	while (tmp_env[i][0] != '\0')
	{	
		write(1, tmp_env[i], ft_strlen(tmp_env[i]));			
		if (tmp_env[i + 1])	
			write (1, "\n", 1);
		i++;
	}
}

void		ls_command(char **command)
{
	pid_t	childID;
	pid_t	endID;

	childID = fork();
	endID = 0;
	if (childID == 0)
		execve("/Users/jterry/dwisoky2/ft_ls", command, NULL);
	while (endID != childID)
		endID = waitpid(childID, NULL, 0);
}

int			all_command(char **command)
{
	pid_t	childID;
	pid_t	endID;
	int		i;

	childID = fork();
	endID = 0;
	if (childID == 0)
		i = execve(command[0], command, NULL);
	while (endID != childID)
		endID = waitpid(childID, NULL, 0);
	return (i);
}

void		pwd_command(char **tmp_env)
{
	char	*home;

	ft_getenv(tmp_env, "PWD", &home);
	ft_putstr(home);
	write(1, "\n", 1);
}

void		echo_command(char **command)
{
	int i;
	int	j;
	int	flag;

	flag = 0;
	j = 1;
	i = 1;
	if (command[i])
	{
		while (command[i][0] == '-')
		{
			while(command[i][j] == 'n')
				j++;
			if (command[i][j])
				break;
			j = 0;
			flag++;
			i++;
		}
		while (command[i])
		{
			write(1, command[i], ft_strlen(command[i]));
			if (command[i + 1])
				write(1, " ", 1);	
			i++;
		}
		if (flag != 0)
			write(1, "\033[7m%\033[0m", 9);
		write(1, "\n", 1);
	}
}
