#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "libft.h"
#include "sh1.h"


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
            ex = pass_str_to_exec((const char **) splited);
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
	char **ptr;

    status = 0;
    pid = -1;
    pid = fork();
	ptr = NULL;
    if (pid == 0)
    {
	ptr = (char **) str;
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
