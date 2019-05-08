/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwisoky <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 16:31:35 by dwisoky           #+#    #+#             */
/*   Updated: 2019/03/25 14:30:26 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(long long int n)
{
	char	s[11];
	char	*str1;
	int		i;
	int		j;

	i = 1;
	j = n < 0 ? -1 : 1;
	s[0] = n % 10 * j + '0';
	n = n / 10;
	while (n * j > 0)
	{
		s[i] = '0' + (j * n) % 10;
		n /= 10;
		i++;
	}
	if (j == -1)
		s[i++] = '-';
	if ((str1 = (char*)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	str1[i] = '\0';
	j = 0;
	while (i--)
		str1[j++] = s[i];
	return (str1);
}
