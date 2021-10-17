#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	char		buf[BUFFER_SIZE +1];
	int			bytes_read;
	char		*leak;
	char		*eol_ptr;
	static char	*remainder;

	//int			flag = 1;

/*	if (remainder)
		line = ft_strdup(remainder);
	else
		line = ft_strdup("");*/
	eol_ptr = check_tail(remainder, &line);

	while (!eol_ptr && (bytes_read = read(fd, buf, BUFFER_SIZE)))
	{
		buf[bytes_read] = '\0';
		if ((eol_ptr = ft_strchr(buf, '\n')))
		{
			*eol_ptr = '\0';
			//flag = 0;
			++eol_ptr;
			leak = remainder;
			remainder = /*ft_strdup(++eol_ptr);*/ft_substr(eol_ptr, 0, BUFFER_SIZE);
			free(leak);
		}
		leak = line;
		line = ft_strjoin(line, buf);
		free(leak);
	}
	
	if (!bytes_read || !ft_strlen(remainder))
		return (NULL);

	return (line);
}

char	*check_tail(char *remainder, char **line)
{
	char	*eol_ptr;

	eol_ptr = NULL;
	if (remainder)
	{
		if ((eol_ptr = ft_strchr(remainder, '\n')))
		{
			*eol_ptr = '\0';
			*line = ft_strdup(remainder);
			ft_strcpy(remainder, ++eol_ptr);
		}
		else
		{
			*line = ft_strdup(remainder);
			//ft_strclr ???
		}
	}
	else
		*line = ft_strdup("");
	return (eol_ptr);
}