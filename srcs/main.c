#include <unistd.h>
#include <sys/wait.h>

#include "libft.h"
#include "minishell.h"

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

int pass_str_to_exec(const char **str, t_sh *shell)
{
    int pid;
    int status;
    char **ptr;

    status = 0;
    pid = fork();
    if (pid == 0)
    {
        ptr = (char **) str;
        execve(str[0], ptr, shell->last_environ);
        return (1);
    }
    else if (pid > 0)
    {
        waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			shell->last_command_ret = WEXITSTATUS(status);
        return (0);
    }
    write(2, "error", 5);
    return (-1);
}

int read_from_stdin(t_sh *shell)
{
    char buf[BUFF_SIZE];
    char *no_spaces;
    char **command;

    display_prompt(shell);
    buf_init(buf, BUFF_SIZE);
    while ((read(0, buf, BUFF_SIZE) > 0))
    {
        if (is_only_endline(buf) || is_only_spaces(buf))
            display_prompt(shell);
        else
        {
            ft_remove_endline(buf);
            no_spaces = ft_remove_useless(buf, ' ');
            command = ft_lz_strsplit(no_spaces, ' ');
            ft_strdel(&no_spaces);
            manage_interpretor(command, shell);
			if (manage_builtins(command, shell))
				;
            else if (make_exploitable(command, shell->last_environ))
            {
                if (pass_str_to_exec((const char **) command, shell) == 1)
                    return (1);
            }
            else
                display_command_not_found(command[0]);
            tab_free(command);
            display_prompt(shell);
        }
        str_clear(buf);
    }
    return (0);
}

int main(void)
{
    int ret;
    t_sh *shell;

    if ((shell = create_shell_props()))
    {
        ret = read_from_stdin(shell);
        clean_program(shell);
        return (ret);
    }
    // Issue in create_shell_props
    return (3);
}
