/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 12:44:46 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/02 15:23:32 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	slen;
	char			*str;

	if (!s)
		return (NULL);
	i = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	slen = ft_strlen(s);
	while (i < len && start < slen)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
