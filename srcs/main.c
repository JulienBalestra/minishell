#include <unistd.h>
#include <sys/wait.h>

#include "libft.h"
#include "minishell.h"

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

int pass_str_to_exec(const char **str, t_sh *shell, char **mock_environ, int mock)
{
    int pid;
    int status;
    char **ptr;

    status = 0;
    ft_str2del(shell->last_command);
    pid = fork();
    if (pid == 0)
    {
        ptr = (char **) str;
		if (mock == 0)
			mock_environ = shell->last_environ;
        execve(str[0], ptr, mock_environ);
        return (1);
    }
    else if (pid > 0)
    {
        waitpid(-1, &status, 0);
		if (WIFEXITED(status))
        {
            shell->last_command_ret = WEXITSTATUS(status);
        }
        return (0);
    }
    write(2, "error", 5);
    return (-1);
}

int read_from_stdin(t_sh *shell)
{
    char ***command;
	int i;

    while (42)
    {
		shell->buf = get_line(shell);
        if (existing_line(shell) && correct_syntax(shell))
        {
            command = build_command(shell);
			i = 0;
            while (shell->exit == 0 && command && command[i])
            {
                if (manage_builtins(command[i], shell))
					;
                else if (make_exploitable(command[i], shell->last_environ))
                {
                    if (pass_str_to_exec((const char **) command[i], shell, NULL, 0) == 1)
                        return (1);
                }
                else
                    display_command_not_found(command[i][0]);
                i++;
            }
            ft_str3del(command);
        }
		if (shell->exit == 1)
			return (0);
    }
}

int main(void)
{
    int ret;
    t_sh *shell;

    if ((shell = create_shell_props()))
    {
        if (read_from_stdin(shell) == 0)
		{
			ret = shell->last_command_ret;
			clean_program(shell);
			return (ret);
		}
		return (2);
    }
    return (3);
}
