#include <stdlib.h>
#include <unistd.h>

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char		*ft_strndup(char *s, int n)
{
	char	*new_str;
	int	i;

	if (!s && ft_strlen(s) > n)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (n));
	if (new_str != NULL)
	{
		i = 0;
		while ((s[i] != '\0') && (i < n))
		{
			new_str[i] = s[i];
			i++;
		}
		new_str[i] = '\0';
	}
	return (new_str);
}

int 	ft_to_trim(char *s, char c, int foreward)
{
	int i;
	int len;

	len = ft_strlen(s); 
	if (foreward != 1)
	{
		i = len;
		while (s[i] == c || i > 0)
	        	i--;
	}
	else 
	{
		i = 0;
		while (s[i] == c || i < len)
	        	i++;
	}
	return (i);
}

char *ft_str_trimed(char *s, char c)
{
	char *trim;
	int len;
	int new_len;

	trim = NULL;
	len = ft_strlen(s);
	new_len = len - ft_to_trim(s, c, 1) - ft_to_trim(s, c, 0);
	if ((len > 0) && (trim = (char *)malloc(sizeof(char) * len)))
	{
		trim = ft_strndup(&s[ft_to_trim(s, c, 1)], len - ft_to_trim(s, c, 0));	
		free(s);
	}
	return (trim);
}
