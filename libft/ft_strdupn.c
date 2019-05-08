/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 16:52:10 by jterry            #+#    #+#             */
/*   Updated: 2019/03/24 17:01:38 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdupn(char const *str2, int n)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char*)malloc(sizeof(*str) * (n + 1))))
		return (NULL);
	while (i < n)
	{
		str[i] = str2[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
