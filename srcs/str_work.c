#include <stdlib.h>
#include <stdio.h>

int	ft_strlen(char *s)
{
	int i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

char *ft_remove_endline(char *str)
{
	char *new_str;
	int len;
	int i;

	new_str = NULL;
	len = ft_strlen(str);
	i = 0;
	if (str[len -1] == '\n')
	{
		if ((new_str = (char *)malloc(sizeof(char) * len)))
		{
			while (i < len -1)
			{
				new_str[i] = str[i];
				i++;
			}
			new_str[i] = '\0';
		}
		return (new_str);
	}
	else
	{
		return (str);
	}
}

char *ft_remove_useless(char *str, char c)
{
	char *new_str;
	int len;
	int s;
	int e;
	int i;

	new_str = NULL;
	len = ft_strlen(str);
	s = 0;
	e = len;
	i = 0;
	while (str[s] == c)
		s++;
	if (s == len)
		return (NULL);
	while (str[e - 1] == c)
		e--;
	e = len - e;
	len = len - (s + e);	
	if ((new_str = (char *)malloc(sizeof(char) * len + 1)))
	{
		while (i < len)
		{
			new_str[i] = str[i + s];
			i++;
		}
		new_str[i] = '\0';
	}
	return (new_str);
}

int main(void)
{
	char *str;
	char cus1[] = " cus1 \n";
	char cus2[] = " cus2  \n";
	char cus3[] = " cus3  \n ";
	char cus4[] = " c us4   \n";
	char trim1[] = "  test ";
	char trim2[] = "test   ";
	char trim3[] = "test";
	
	str = ft_remove_endline(cus1);
	printf("\n[%s]", str);
	free(str);
	str = ft_remove_endline(cus2);
	printf("\n[%s]", str);
	free(str);
	
	str = ft_remove_endline(cus3);
	printf("\n[%s]", str);
	str = ft_remove_endline(cus4);
	printf("\n[%s]", str);
	free(str);

	str = ft_remove_useless(trim1, ' ');
	printf("\ntrim1:[%s]:[%s]\n", trim1, str);
	free(str);

	str = ft_remove_useless(trim2, ' ');
	printf("\ntrim2:[%s]:[%s]\n", trim2, str);
	free(str);

	str = ft_remove_useless(trim3, ' ');
	printf("\ntrim3:[%s]:[%s]\n", trim3, str);
	free(str);

	return (0);
}
