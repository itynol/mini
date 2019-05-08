/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:57:31 by jterry            #+#    #+#             */
/*   Updated: 2019/05/08 20:41:14 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <pwd.h>
#include <limits.h>
#include "libft/libft.h"

typedef struct		s_cmd
{
	char			*name;
	char			*path;
	struct _cmd		*next;
}					t_cmd;

void		unsetenv_command(char ***tmp_env, char **command);
char		**ft_envadd(char **env, int flag, int pos);
void		setenv_command(char ***tmp_env, char **command);
char		**ft_setenv(char **tmp_env, char *str, char *str2);
int			all_command(char **command);
void		echo_command(char **command);
void		cd_command(char **command, char **tmp_env);
void		change_pwd(char **tmp_env, char **com);
int			ft_getenv(char **tmp_env, char *str, char **buf);
void		env_command(char **tmp_env);
void		ls_command(char **command);
void		pwd_command(char **tmp_env);
#endif
