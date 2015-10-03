#ifndef SH1_H
# define SH1_H


void str_clear(char *str);
void buf_init(char *buf, int len);

int tab_len(char **tab);
void tab_free(char **tab);

char *ft_remove_endline(char *str);

//main
int pass_str_to_exec(const char **str);

#endif
