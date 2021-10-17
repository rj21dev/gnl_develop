#include "get_next_line.h"

char	*is_remainder(char *remainder, char **line)
{
	char	*eolPtr;

	eolPtr = NULL;
	if (remainder)
		if ((eolPtr = ft_strchr(remainder, '\n')))
		{
			*line = ft_substr(remainder, 0, eolPtr - remainder + 1);
		}
		else
			*line = ft_strdup(remainder);
	else
		*line = ft_strdup("");
	return (eolPtr);
}

char	*get_remainder(int fd, char *remainder, int *bytes_read)
{
	char	buf[BUFFER_SIZE +1];
	char	*leak;

	while ((*bytes_read = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[*bytes_read] = '\0';
		if (remainder)
		{
			leak = remainder;
			remainder = ft_strdup(buf);
			free(leak);
		}
		else
			remainder = ft_strdup(buf);
		if (ft_strchr(remainder, '\n'))
			break;
	}
	return (remainder);
}

char	*update_remainder(char *remainder)
{
	char	*leak;
	char	*eol_ptr;

	eol_ptr = NULL;
	if (remainder)
		if ((eol_ptr = ft_strchr(remainder, '\n')))
		{
			leak = remainder;
			remainder = ft_substr(remainder, eol_ptr - remainder + 1, BUFFER_SIZE);
			free(leak);
		}
	return (remainder);
}

char	*get_next_line(int fd)
{
	int			bytes_read;
	static char	*remainder; 
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = get_remainder(fd, remainder, &bytes_read);
	if (bytes_read <= 0)
		return (NULL);
	if (is_remainder(remainder, &line))
		remainder = update_remainder(remainder);
	else
	{
		free(remainder);
		remainder = NULL;
	}
	return (line);
}
