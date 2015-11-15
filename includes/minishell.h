#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFF_SIZE      4096

# define PROMPT "minishell> "
# include <string.h>

// data model
typedef struct		s_env
{
    struct s_env	*next;
    struct s_env	*prev;
    char			*name;
    char 			*value;
}					t_env;

typedef struct		s_sh
{
    t_env			*env;
    char			**last_environ;
	char			*prompt;
	size_t			len_prompt;
	int 			last_command_ret;
	int 			exit;
}					t_sh;

// misc_string
void				str_clear(char *str);
void				buf_init(char *buf, int len);
char *triple_join(char *s1, char *s2, char *s3);

// misc_array
int tab_len(char **tab);
void tab_free(char **tab);

// input_format
void ft_remove_endline(char *str);
int is_only_endline(char *buf);
int is_only_spaces(char *buf);

// misc_prompt
void display_prompt(t_sh *shell);
void display_command_not_found(char *command);

int     make_exploitable(char **command, char **last_environ);
int strlen_until_char(char *str, char c);

void override_last_environ(t_sh *shell);
void clean_program(t_sh *shell);
// main
int pass_str_to_exec(const char **str, t_sh *shell);
int manage_builtins(char **command, t_sh *shell);
void builtin_env(char **last_environ);
void builtin_unsetenv(char **command, t_sh *shell);
void builtin_setenv(char **command, t_sh *shell);
void manage_interpretor(char **command, t_sh *shell);
void builtin_exit(char **command, t_sh *shell);
void builtin_getenv(char **command, t_sh *shell);
char *get_env_value(char *name, t_env *env);

t_sh    *create_shell_props(void);

#endif
