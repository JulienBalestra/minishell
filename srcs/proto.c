#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

static int	ft_nb_string(char const *s, char sep, int len)
{
    int		i;
    int		nb_sep;

    i = 0;
    nb_sep = 0;
    while (i < len)
    {
        if ((s[i] == sep) && (i != 0))
        {
            if (s[i - 1] != sep)
                nb_sep++;
        }
        i++;
    }
    if (i != 0)
        nb_sep++;
    return (nb_sep);
}

static char *ft_strnew_n_to_i_alloc(char const *s, int n, int i)
{
    char	*str;
    int		k;

    str = (char *)malloc(sizeof(char) * (size_t)(i - n));
    k = 0;
    if (str)
    {
        while (n != i)
        {
            str[k] = s[n];
            n++;
            k++;
        }
        str[k] = '\0';
    }
    return (str);
}

static void	ft_do_split(char const *s, char sep, int len, char **split)
{
    int		k;
    int		n;
    int		i;

    k = 0;
    n = -1;
    i = 0;
    while (i < len)
    {
        if (s[i] != sep)
        {
            if (n == -1)
                n = i;
            if (i == len - 1)
                split[k] = ft_strnew_n_to_i_alloc(s, n, i + 1);
        }
        else if ((i != 0) && (s[i - 1] != sep))
        {
            split[k] = ft_strnew_n_to_i_alloc(s, n, i);
            k++;
            n = -1;
        }
        i++;
    }
}

char		**ft_strsplit(char const *s, char c)
{
    char	**split;
    int		len;

    len = ft_strlen(s);
    while ((s[len - 1] == c) && (len >= 0))
        len--;
    split = (char **)malloc(sizeof(char *) *
                            (size_t)ft_nb_string(s, c, len) + 1);
    if (split == NULL)
        return (NULL);
    ft_do_split(s, c, len, split);
    split[ft_nb_string(s, c, len)] = NULL;
    return (split);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (*str)
    {
        str++;
        i++;
    }
    return (i);
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
    while (tab[i])
    {
        i++;
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

char **build_opt(char **str)
{
    char **opt;
    int i;

    i = 1;
    opt = (char **)malloc(sizeof(char *) * tab_len(str));
    while (str[i])
    {
        opt[i] = str[i];
        i++;
    }
    opt[i] = NULL;
    return (opt);
}

void str_clear(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
	str[i] = '\0';
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
    char **opt;

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
            parsed = char_remove(buf, '\n');
	        str_clear(buf);
            splited = ft_strsplit(parsed, ' ');
            opt = build_opt(splited);
            ex = pass_str_to_exec(splited, opt);
            if (ex == 0) 
		write(1, "> ", 2);
	    else
	    {
		free(parsed);
		tab_free(splited);
		tab_free(opt);
		return (1);
	    }
	}
    }
    return (-1);
}

int pass_str_to_exec(const char **str, char **opt)
{
    int pid;
    int status;

    status = 0;
    pid = -1;
    pid = fork();
    if (pid == 0)
    {
        if (opt[0] == NULL)
	{
            execve(str[0], &str[0], NULL);
	}
	else
            execve(str[0], &opt[0], NULL);
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
