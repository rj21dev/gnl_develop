#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	char		*leak;
	char		buf[BUFFER_SIZE + 1];
	char		*eolPtr;
	static char	*tail;
	int			byteIsRead;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	eolPtr = check_tail(tail, &line);
	while (!eolPtr && (byteIsRead = read(fd, buf, BUFFER_SIZE)))
	{
		buf[byteIsRead] = '\0';
		if ((eolPtr = ft_strchr(buf, '\n')))
		{
			*eolPtr = '\0';
			tail = ft_strdup(++eolPtr); 
		}
		leak = line;
		line = ft_strjoin(line, buf);
		free(leak);
	}
	if (!byteIsRead)
		return (NULL);
	return (line);
}

char	*check_tail(char *tail, char **line)
{
	char	*eolPtr;

	eolPtr = NULL;
	if (tail)
		if ((eolPtr = ft_strchr(tail, '\n')))
		{
			*eolPtr = '\0';
			*line = ft_strdup(tail);
			ft_strcpy(tail, ++eolPtr);
		}
		else
			*line = ft_strdup(tail);
	else
		*line = ft_strdup("");
	return (eolPtr);
}
