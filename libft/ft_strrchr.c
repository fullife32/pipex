/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:03:52 by eassouli          #+#    #+#             */
/*   Updated: 2019/10/27 15:12:36 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	*str;

	i = ft_strlen(s);
	str = (unsigned char *)s;
	while (i >= 0)
	{
		if (str[i] == c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
