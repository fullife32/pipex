/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:51:58 by eassouli          #+#    #+#             */
/*   Updated: 2019/11/05 11:00:49 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*source;

	i = 0;
	dest = dst;
	source = (unsigned char *)src;
	while (i < n)
	{
		dest[i] = source[i];
		if (dest[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
