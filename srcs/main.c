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
    int fork_ret;
    char buf[BUFF_SIZE];
    char *no_end;
    char *no_spaces;
    char **splited;

    ret = 0;
    fork_ret = -2;
    no_end = NULL;
    no_spaces = NULL;
    splited = NULL;

    write(1, "> ", 2);
    buf_init(buf, BUFF_SIZE);
    while ((ret = read(0, buf, BUFF_SIZE) > 0))
    {
        if (is_eof(buf))
            return (0);
        else if (is_only_endline(buf) || is_only_spaces(buf))
            ;
        else
        {
            no_end = ft_remove_endline(buf);
            no_spaces = ft_remove_useless(no_end, ' ');
            free(no_end);
            no_end = NULL;
            splited = ft_lz_strsplit(no_spaces, ' ');
            free(no_spaces);
            no_spaces = NULL;
            fork_ret = pass_str_to_exec((const char **) splited);
            tab_free(splited);
            if (fork_ret != 0)
            {
                return (1);
            }
        }
        str_clear(buf);
        write(1, "> ", 2);
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
