#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "libft.h"
#include "minishell.h"

int pass_str_to_exec(const char **str)
{
    int pid;
    int status;
    char **ptr;
    int ret;

    status = 0;
    pid = -1;
    ptr = NULL;
    ret = -1;

    pid = fork();
    if (pid == 0)
    {
        ptr = (char **) str;
        ret = execve(str[0], ptr, NULL);
        return (ret);
    }
    else if (pid > 0)
    {
        waitpid(-1, &status, 0);
        return (1);
    }
    write(2, "error", 5);
    return (-1);
}

int read_from_stdin(void)
{
    int ret;
    int fork_ret;
    char buf[BUFF_SIZE];
    char *no_end;
    char *no_spaces;
    char **command;

    ret = 0;
    fork_ret = -2;
    no_end = NULL;
    no_spaces = NULL;
    command = NULL;
    display_prompt();
    buf_init(buf, BUFF_SIZE);
    while ((ret = read(0, buf, BUFF_SIZE) > 0))
    {
        if (is_only_endline(buf) || is_only_spaces(buf))
            display_prompt();
        else
        {
            no_end = ft_remove_endline(buf);
            no_spaces = ft_remove_useless(no_end, ' ');
            ft_strdel(&no_end);
            command = ft_lz_strsplit(no_spaces, ' ');
            ft_strdel(&no_spaces);
            if (make_exploitable(command))
            {
                if ((fork_ret = pass_str_to_exec((const char **) command)) && fork_ret != 1)
                    return (fork_ret);
            }
            else
            {
                ft_putstr_fd(command[0], 2);
                ft_putstr_fd(": command not found\n", 2);
            }
            tab_free(command);
            display_prompt();
        }
        str_clear(buf);
    }
    return (0);
}

int main(void)
{
    int ret;

    ret = read_from_stdin();
    return (ret);
}
