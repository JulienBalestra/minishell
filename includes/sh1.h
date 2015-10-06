#ifndef SH1_H
# define SH1_H

# define BUFF_SIZE      4096

void str_clear(char *str);
void buf_init(char *buf, int len);

int tab_len(char **tab);
void tab_free(char **tab);

char *ft_remove_endline(char *str);
int is_only_endline(char *buf);
int is_only_spaces(char *buf);
int is_eof(char *buf);

char **environ(void);

//main
int pass_str_to_exec(const char **str);

#endif
