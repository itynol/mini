/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 21:39:09 by jterry            #+#    #+#             */
/*   Updated: 2019/05/09 06:02:43 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check(char c)
{
	if (c == '#' || c == '%' || c == '!' || c == '@' || c == '"' || c == 39
			|| c == '^' || c == '*' || c == '(' || c == ')'
			|| c == '=' || c == '/')
		return (0);
	return (1);
}

char		*ft_dollar_word(char *str, char **tmp_env)
{
	char	*tmp;
	int		i;
	int		k;
	char	**tmp_g;
	
	i = 0;
	k = -1;
	if (str[i] && str[i] == '$')
		return(ft_itoa(getpid()));
	while (str[i] && ft_check(str[i]))
		i++;
	tmp = malloc (i + 1);
	while (++k < i)
		tmp[k] = str[k];
	tmp[k] = '\0';
	if ((k = ft_getenv(tmp_env, tmp, NULL)) < 0)
		return (0);
	tmp_g = ft_strsplit(tmp_env[k], '=');
	free(tmp);
	tmp = tmp_g[1];
	free(tmp_g);
	free(tmp_g[0]);
	return (tmp);
}	

char		**ft_dollar(char *com ,char **tmp_env)
{
	char	**commands;
	int		i;
	int		j;
	char	*tmp;
	int		l;
	char	*kek;

	i = 0;
	j = 0;
	commands = ft_strsplit(com, ' ');
	while (commands[++i])
	{
		while (commands[i][j] != '\0')
		{
			if (commands[i][j] == '$' && commands[i][j + 1])
			{
				tmp = ft_dollar_word(&commands[i][j + 1], tmp_env);
				l = j;
				if (commands[i][j + 1] == '$')
					j++;
				else
					while (commands[i][j] && ft_check(commands[i][j]))
						j++;
				kek = ft_strdup(&commands[i][j]);
				commands[i][l]  = '\0';
				if (tmp)
					commands[i] = ft_strrejoin(commands[i], tmp, 3);
  				if (kek)
					commands[i] = ft_strrejoin(commands[i], kek, 3);
			}
			j++;
		}
		j = 0;
	}
	return (commands);
}
