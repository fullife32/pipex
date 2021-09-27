/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:40:15 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/02 14:52:39 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	n;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		j = i;
		n = 0;
		while (needle[n] == haystack[j] && j < len)
		{
			j++;
			n++;
			if (needle[n] == '\0')
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
