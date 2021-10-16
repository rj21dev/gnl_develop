#include <stdio.h>
#include <stdlib.h>

void	foo(char *str);

int	main(void)
{
	foo("test");
	foo("best");
	foo("next");
}

void	foo(char *str)
{
	static char	*dst;
	static int	n;
	int			i;
	int			j;

	if (!dst)
	{
		dst = (char *) malloc(sizeof(char) * (100 + 1));
		if (!dst)
			return ;
	}	
	i = 0;
	while (dst[i])
		++i;
	j = 0;
	while (str[j])
	{
		dst[i] = str[j];
		++i;
		++j;
	}
	dst[i] = 0;
	printf("%s\n", dst);
	++n;
	if (n == 3)
		free(dst);
}
