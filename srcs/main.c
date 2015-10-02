#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

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
	if ((new_str = (char *)malloc(sizeof(char) * (len + 1))))
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
	if ((new_str = (char *)malloc(sizeof(char) * (n +1))))
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

int ft_strlen_without(char *str, char c)
{
    int i;

    i = 0;
    while (*str)
    {
        if (*str != c)
            i++;
        str++;
    }
    return (i);
}

char *char_remove(char *str, char c)
{
    int len;
    char *new_str;
    int i;

    len = ft_strlen_without(str, c);
    new_str = NULL;
    i = 0;
    if ((new_str = (char *)malloc(sizeof(char) * len)))
    {
        while (str[i] != '\0')
        {
            if (str[i] != c)
                new_str[i] = str[i];
            i++;
        }
    }

    return (new_str);
}

int tab_len(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			i++;
		}
	}
	return (i);
}

void tab_free(char **tab)
{
   int i;

   i = 0;
   while (tab[i])
   {
	free(tab[i]);
	i++;
   }
}

void str_clear(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
	str[i] = '\0';
	i++;
    }
}

void buf_init(char *buf, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
	buf[i] = '\0';
	i++;
    }
}

int read_from_stdin(void)
{
    int ret;
    int ex = -2;
    char buf[4096];
    char *parsed;
    char **splited;

    ret = 0;
    parsed = NULL;
    write(1, "> ", 2);
    buf_init(buf, 4096);
    while ((ret = read(0, buf, 4096) > 0))
    {
	if (buf[0] == '\n' && buf[1] == '\0')
		write(1, "> ", 2);
	else
	{	
            parsed = ft_remove_endline(buf);
	        str_clear(buf);
		parsed = ft_remove_useless(parsed, ' '); 
		splited = NULL;
            splited = ft_lz_strsplit(parsed, ' ');
		free(parsed);
		parsed = NULL;
            ex = pass_str_to_exec(splited);
            if (ex == 0) 
		write(1, "> ", 2);
	    else
	    {
		tab_free(splited);
		return (1);
	    }
	}
    }
    return (-1);
}

int pass_str_to_exec(const char **str)
{
    int pid;
    int status;
	char ***ptr;

    status = 0;
    pid = -1;
    pid = fork();
	ptr = NULL;
    if (pid == 0)
    {
	ptr = &str[0];
        execve(str[0], ptr, NULL);
	return (1);
    }
    else if (pid > 0)
    {
        waitpid(-1, &status, 0);
	return (0);
    }
    else
        write(2, "error", 5);

    return (-1);
}

int main(void)
{
   read_from_stdin();
    return (1);
}
