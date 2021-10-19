/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:34:47 by rjada             #+#    #+#             */
/*   Updated: 2021/10/19 21:34:56 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*eol_ptr;
	char		*tmp;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (remainder)
	{
		eol_ptr = ft_strchr(remainder, '\n');
		if (eol_ptr)
		{
			line = ft_substr(remainder, 0, eol_ptr - remainder + 1);
			tmp = ft_substr(remainder, eol_ptr - remainder + 1, BUFFER_SIZE);
			free(remainder);
			remainder = tmp;
			return (line);
		}
		line = remainder;
		remainder = NULL;
	}
	else
		line = ft_realloc(line, 1);
	return (read_from_fd(fd, &remainder, &line));
}

char	*read_from_fd(int fd, char **remainder, char **line)
{
	char	buf[BUFFER_SIZE + 1];
	char	*eol_ptr;
	int		len;
	int		bytes_read;

	len = ft_strlen(*line) + 1;
	while (1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		buf[bytes_read] = '\0';
		if (bytes_read <= 0)
			return (eof_errno_case(bytes_read, remainder, line));
		eol_ptr = ft_strchr(buf, '\n');
		if (eol_ptr)
			break ;
		len += bytes_read;
		*line = ft_realloc(*line, len);
		ft_strlcat(*line, buf, len);
	}
	len += eol_ptr - buf + 1;
	*line = ft_realloc(*line, len);
	ft_strlcat(*line, buf, len);
	*remainder = ft_substr(buf, eol_ptr - buf + 1, BUFFER_SIZE);
	return (*line);
}

char	*eof_errno_case(int bytes_read, char **remainder, char **line)
{
	int	len;

	len = ft_strlen(*line);
	if ((*line && bytes_read < 0) || (*line && !len && !bytes_read))
	{
		free(*line);
		*line = NULL;
	}
	if (*remainder && bytes_read < 0)
	{
		free(*remainder);
		*remainder = NULL;
	}
	return (*line);
}

void	*ft_realloc(void *src, size_t size)
{
	void	*dst;
	size_t	i;

	dst = malloc(size);
	if (!dst)
		return (NULL);
	i = 0;
	while (src && i < size && ((char *)src)[i])
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	((char *)dst)[i] = '\0';
	free(src);
	return (dst);
}
