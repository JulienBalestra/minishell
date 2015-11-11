#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFF_SIZE      4096

# define PROMPT "minishell> "
# include <string.h>

// data model
typedef struct		s_env
{
    struct s_env	*next;
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


t_sh    *create_shell_props(void);

#endif
