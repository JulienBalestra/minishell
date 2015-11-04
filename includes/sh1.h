#ifndef SH1_H
# define SH1_H

# define BUFF_SIZE      4096

# define PROMPT "minishell> "
# define PROMPT_SIZE 11

// misc_string
void str_clear(char *str);
void buf_init(char *buf, int len);

// misc_array
int tab_len(char **tab);
void tab_free(char **tab);

// input_format
char *ft_remove_endline(char *str);
int is_only_endline(char *buf);
int is_only_spaces(char *buf);

// misc_prompt
void display_prompt(void);

// main
int pass_str_to_exec(const char **str);

// data model
typedef struct			s_sh
{
    int					ret;
    char                **env;
}						t_sh;

#endif
