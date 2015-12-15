/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 16:27:24 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 16:27:26 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define READ      128
# define CWD       2048
# define PROMPT "minishell> "
# define USE_CWD	1
# include <string.h>

typedef struct		s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*name;
	char			*value;
}					t_env;
typedef struct		s_sh
{
	t_env			*env;
	struct s_sh		*mock;
	char			**l_env;
	char			*ps1;
	size_t			len_ps1;
	int				l_ret;
	char			**l_cmd;
	char			*buf;
	int				exit;
}					t_sh;
typedef struct		s_be
{
	int				ignore;
	int				unet;
	int				set;
	int				null;
	int				cmd;
}					t_be;
char				*triple_join(char *s1, char *s2, char *s3);
void				ft_remove_endchar(char *str, char c);
int					is_only_endline(char *buf);
int					is_only_spaces(char *buf);
void				display_prompt(t_sh *shell);
void				display_command_not_found(char *command);
int					make_exploitable(char **command, char **last_environ);
int					len_to_char(char *str, char c);
char				**override_last_environ(t_sh *shell);
char				**build_tab_environ(t_env *env);
void				clean_program(t_sh *shell);
int					do_fork(const char **str, t_sh *shell,
								char **mock_environ, int mock);
int					manage_builtins(char **command, t_sh *shell);
void				builtin_env(char **command, t_sh *shell);
void				builtin_unsetenv(char **command, t_sh *shell);
void				builtin_setenv(char **command, t_sh *shell);
void				manage_interpretor(char **command, t_sh *shell);
void				builtin_exit(char **command, t_sh *shell);
void				builtin_getenv(char **command, t_sh *shell);
char				*get_env_value(char *name, t_env *env);
void				builtin_cd(char **command, t_sh *shell);
void				ft_setenv(char *name, char *value, t_sh *shell);
void				convert_chars(char *str);
t_env				*create_env_link(t_env *env, char *environ_entry);
t_sh				*create_shell_from(char **environ_tab);
t_sh				*create_shell_props(void);
t_env				*manage_empty_environ(void);
int					is_ignore_arg(char *arg);
int					is_null_arg(char *arg);
int					have_unsets(char **command);
int					is_only_env(char **command);
int					have_null(char **command);
int					have_ignore(char **command);
int					have_setenv(char **command);
int					is_setenv(char *arg);
int					have_command(char **command);
int					is_benv_errors(t_be *benv);
void				display_environ(char **to_display, int end_line);
void				display_only_setenv(char **command, int end_line);
int					is_benv_do_nothing(t_be *benv);
void				run_under_new_environ(char **command, t_sh *shell);
t_env				*get_start(t_env *env);
void				delete_list(t_env **env);
void				display_not_such(char *who, char *where);
char				**get_mock_environ(char **command);
t_env				*upsert_link(t_env *env, char *environ_entry);
void				run_under_alter_environ(char **command,
											t_sh *shell);
char				**merge_both_environ(char **first,
									char **unset, char **second);
void				destroy_env_link(t_env *env);
size_t				len_env(t_env *env);
t_env				*get_end(t_env *env);
void				alter_environ_and_display(char **command,
											t_sh *shell, int end_lines);
int					is_d_var(char *variable);
char				*transform_dollar_builtin(char *entry, t_sh *shell);
int					is_dollar_builtin(char *entry);
char				*replace_dollar_dollar(char *dollar_question);
char				*replace_dollar_question(char *dollar_question,
												t_sh *shell);
int					is_real_line(char *buf);
char				***build_command(t_sh *shell);
char				*get_line(t_sh *shell);
int					existing_line(t_sh *shell);
void				go_to_old_pwd(t_sh *shell, int p);
void				go_to_home_directory(t_sh *shell);
void				change_dir(char *path, t_sh *shell, int p);
int					is_enter(char *buf);
int					cust_atoi(const char *nptr);
int					correct_syntax(t_sh *shell);
void				ft_str3del(char ***str);
void				display_permission_denied(const char *command);
int					is_goto_home(char **command);
void				ensure_pwd(t_sh *shell);
char				*remove_duplicate_slash(char *path);
void				display_is_directory(const char *command);
void				transform_tilde(char **command, t_sh *shell);
int					is_tilde_transform(char *str, char c);
char				*troncate_dots(char *path);
int					is_logical_goto_oldpwd(char **str);
int					is_physical_goto_oldpwd(char **str);
int					is_legal_options(char **str, t_sh *shell);
void				display_cd_invalid_option(char *opt);
int					is_physical(char *str);
int					is_logical(char *str);
int					is_minus(char *str);
char				*create_cwd(t_sh *shell);
char				*create_chdir_path(char *path, t_sh *shell);
void				display_cd_permission(char *path);
void				cd_symblink(char *path, t_sh *shell);
#endif
