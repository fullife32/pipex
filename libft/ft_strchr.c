/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:38:47 by eassouli          #+#    #+#             */
/*   Updated: 2019/10/26 11:19:11 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return ((char *)s + i);
		i++;
	}
	if (str[i] == c)
		return ((char *)s + i);
	return (NULL);
}
