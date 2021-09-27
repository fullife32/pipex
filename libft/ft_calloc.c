/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 20:20:13 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/02 15:26:40 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*ptr;

	i = count * size;
	ptr = (unsigned char *)malloc(i);
	if (ptr == NULL)
		return (NULL);
	while (i-- != 0)
		ptr[i] = '\0';
	return ((void *)ptr);
}
