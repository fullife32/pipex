/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 12:44:59 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/02 15:24:46 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_isset(char s, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] != '\0' && ft_isset(s1[start], set) == 1)
		start++;
	len = ft_strlen(&s1[start]);
	while (len > 0 && ft_isset(s1[start + len - 1], set) == 1)
		len--;
	return (ft_substr(s1, start, len));
}
