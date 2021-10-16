#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 10

int	main(void)
{
	char	*buf;
	size_t	bytesToRead;
	size_t	bytesRead;
	ssize_t	currentlyRead;
	int		fd;

	buf = (char *) malloc(sizeof(char) * (BUF_SIZE + 1));
	if (!buf)
		return (1);
	
	fd = 0;
	bytesToRead = BUF_SIZE;
	bytesRead = 0;
	while (bytesRead < bytesToRead)
	{
		currentlyRead = read(fd, buf + bytesRead, bytesToRead - bytesRead);
		if (currentlyRead == -1)
		{
			write(2, "Reading error\n", 14);
			return (1);
		}
		bytesRead += currentlyRead;
	}
	printf("%s\n", buf);
	free(buf);
}
