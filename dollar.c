/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 21:39:09 by jterry            #+#    #+#             */
/*   Updated: 2019/05/08 21:42:23 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		

char		**ft_dollar(char **com ,char **tmp_env)
{
	char	**commands;
	int		i;


	commands = ft_strsplplit(com, ' ');
	while (commands[++i])
	{
		ft_dollar_word(commands[i]);
	}
}
