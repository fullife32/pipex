/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:22:59 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/02 15:17:45 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_leak(char **split, int tab)
{
	while (tab >= 0)
	{
		free(split[tab]);
		tab--;
	}
	free(split);
	return (NULL);
}

static char	*ft_sep(char const *s, char c, size_t i)
{
	size_t	l;
	size_t	t;
	char	*split;

	l = i;
	while (s[l] != '\0' && s[l] != c)
		l++;
	split = malloc(sizeof(char) * (l - i + 1));
	if (split == NULL)
		return (NULL);
	t = 0;
	while (i < l)
	{
		split[t] = s[i];
		i++;
		t++;
	}
	split[t] = '\0';
	return (split);
}

static char	**ft_alloc(char const *s, char c)
{
	size_t	i;
	size_t	b;
	size_t	w;
	char	**split;

	i = 0;
	b = 0;
	w = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			b = 0;
		else if (s[i] != c && b == 0)
		{
			b = 1;
			w++;
		}
		i++;
	}
	split = malloc(sizeof(char *) * (w + 1));
	if (split == NULL)
		return (NULL);
	return (split);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	int		tab;
	char	**split;

	split = ft_alloc(s, c);
	if (split == 0)
		return (NULL);
	i = 0;
	tab = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			split[tab] = ft_sep(s, c, i);
			if (split[tab] == 0)
				return (ft_leak(split, tab));
			while (s[i] != '\0' && s[i] != c)
				i++;
			i--;
			tab++;
		}
		i++;
	}
	split[tab] = 0;
	return (split);
}
