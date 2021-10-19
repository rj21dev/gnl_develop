/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:35:30 by rjada             #+#    #+#             */
/*   Updated: 2021/10/19 21:35:38 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != (char)c)
		++i;
	if (s[i] != (char)c)
		return ((void *)0);
	return (&((char *)s)[i]);
}

size_t	ft_strlen(const char *s)
{
	if (!*s)
		return (0);
	return (ft_strlen(++s) + 1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		res = (char *) malloc(sizeof(char));
		res[0] = 0;
		return (res);
	}
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	res = (char *) malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s[i] && i < len)
	{
		res[i] = s[start + i];
		++i;
	}
	res[i] = 0;
	return (res);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dlen;

	dlen = ft_strlen(dst);
	i = dlen;
	j = 0;
	if (dlen < dstsize - 1 && dstsize > 0)
	{
		while (src[j] && dlen + j < dstsize - 1)
		{
			dst[i] = src[j];
			++i;
			++j;
		}
		dst[i] = 0;
	}
	if (dlen >= dstsize)
		dlen = dstsize;
	return (dlen + ft_strlen(src));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	if (!dstsize)
		return (len);
	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = 0;
	return (len);
}
