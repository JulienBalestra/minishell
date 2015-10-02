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

int	ft_count_string(char *str, char c)
{
	int i;
	int n;
	
	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == c && str[i - 1] != c)
			n++;
		i++;
	}
	return (++n);
}

char *str_range_dup(char *str, int n)
{
	char *new_str;
	int i;

	new_str = NULL;
	i = 0;
	if ((new_str = (char *)malloc(sizeof(char) * n +1)))
	{
		while (i < n)
		{
			new_str[i] = str[i];
			i++;			
		}
		new_str[i] = '\0';		
	}
	return (new_str);
}

char *move_into_substring(char *str, char c, int match)
{	
	if (match)
	{
		while (*str == c)
			str++;
	}
	else
	{
		while (*str && *str != c)
			str++;
	}
	return (str);
}

int get_next_sep(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char **ft_lz_strsplit(char *str, char c)
{
	char **split;
	int nb_str;
	int i;
	int range;

	split = NULL;
	nb_str = ft_count_string(str, c);
	i = 0;
	range = 0;
	if ((split = (char **)malloc(sizeof(char *) * (nb_str + 1))))
	{	
		while (i < nb_str)
		{
			if (i != 0)
				str = move_into_substring(str, c, 1);
			range = get_next_sep(str, c);
			split[i] = str_range_dup(str, range);
			str = move_into_substring(str, c, 0);
			i++;
		}
		split[nb_str] = NULL;
	}
	return (split);	
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
	
	char split1[] = "test a";
	char split2[] = "test  b";
	char split3[] = "test";
	
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

	printf("\nsplit1 nb[%i]:[%s]\n", ft_count_string(split1, ' '), split1);
	for (int i=0; i < ft_count_string(split1, ' '); i++)
		puts(ft_lz_strsplit(split1, ' ')[i]);

	printf("\nsplit2 nb[%i]:[%s]\n", ft_count_string(split2, ' '), split2);
	for (int i=0; i < ft_count_string(split2, ' '); i++)
		puts(ft_lz_strsplit(split2, ' ')[i]);

	printf("\nsplit3 nb[%i]:[%s]\n", ft_count_string(split3, ' '), split3);
	for (int i=0; i < ft_count_string(split3, ' '); i++)
		puts(ft_lz_strsplit(split3, ' ')[i]);


	return (0);
}
