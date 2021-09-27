/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:01:57 by eassouli          #+#    #+#             */
/*   Updated: 2019/10/27 13:59:06 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;

	dest = dst;
	source = (unsigned char *)src;
	if (dest > source)
	{
		while (len-- != 0)
			dest[len] = source[len];
	}
	else
		ft_memcpy(dest, source, len);
	return (dst);
}
