#include <stdlib.h>

int main(void)
{
	char *str;
	int i;

	i = 0;
	str = malloc(1);
	while (i != -1)
	{
	str[i] = 'o';
	i++;
	}
	return (0);
}
