/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:18:01 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 19:21:58 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "libft.h"
# include "ft_lineedit.h"
# include "ft_lexer.h"
# include "ft_term_caps.h"
# include "jobs.h"
# include "error.h"
// # include "redir_exec.h"
// # include "ast.h"
# include "hashtable.h"


# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <dirent.h>

typedef struct			s_listenv
{
	char				*str_env;
	struct s_listenv	*next;
}						t_listenv;

typedef struct			s_env
{
	t_listenv			*copy_list_env;
	int					options_env;
	int					nb_arg;
}						t_env;

typedef struct			s_mini
{
	char				**tab_env;
	char				**tab_argv_split;
	char				*good_path;
	int					last_return_son;
	int					nb_arg;
	int					nb_mail;
	int					no_path;
	int					pipe_on;
	t_listenv			*list_env;
	t_listenv			*list_set;
	t_listenv			*list_final_eof;
	t_bool				bg;
	t_job				*jobs;
	t_ht				*ht[HT_SIZE];
	t_ht				*alias[HT_SIZE];
}						t_mini;

typedef struct			s_buil
{
	char				*arg_built;
	int					(*fct)(t_mini *shell);
}						t_buil;

int						builtin_exit(t_mini *minishell);
int						builtin_history(t_mini *shell);
int						builtin_cd(t_mini *minishell);
int						builtin_echo(t_mini *minishell);
int						builtin_env(t_mini *minishell);
int						builtin_setenv(t_mini *minishell);
int						builtin_unsetenv(t_mini *minishell);
int						builtin_set(t_mini *shell);
int						builtin_unset(t_mini *shell);
int						builtin_export(t_mini *shell);
int						builtin_fg(t_mini *shell);
int						builtin_bg(t_mini *shell);
int						builtin_jobs(t_mini *shell);
int						builtin_hash(t_mini *shell);
int						builtin_unalias(t_mini *shell);
int						builtin_alias(t_mini *shell);
int						pars_hash_args(char **argv, int *reset,
								char **path, int *cmd_index);
int						print_hash_error(int err_type, char *cmd);
int						check_builtin(t_mini *minishell, char **tabb);
t_err					check_variable_to_add(t_mini *s, char **t);
/* BUILTIN ENV */
int						regenere_tab_env(t_mini *shell, t_env *envs);
void					unsetenv_via_env(t_mini *shell, t_env *env, int *x);
void					create_empty_list(t_listenv **tmp, char *str);
t_err					do_a_copy_env(t_mini *s, t_env *envs, t_listenv **env);
void					create_or_add_to_empty_list(t_mini *shell, int i);
void					remplace_variable_env(t_mini *shell, char *str);
void					free_tab_env_use_local(t_mini *shell);
int						change_env_and_join_local(t_mini *shell, char *str);
int						recup_all_options_env(char **tabb, t_env *envs, int *i);
int						apply_options_env(t_mini *shell, t_env *envs, int *i);
int						check_channge_variable_env(t_mini *s, t_env *envs, \
						int *i, int j);
int						start_command(t_mini *shell, t_env *envs, int *i);
void					print_list_for_env(t_mini *shell, t_env *envs);
/* FUNC FREE */
void					free_list_shell(t_listenv **list);
void					free_struct_shell(t_mini *shell);
t_err					free_tab_in_struct(t_mini *shell, int i);
/* Func Create List */
t_err					create_list(t_listenv **list, char **env, int i);
t_err					add_to_list(t_listenv **list, char *str);
t_err					create_list_for_setenv(t_listenv **list, char *str);
t_err					create_copy_list(t_listenv **dst, t_listenv **src);
/* Func general */
t_err					recup_env(t_mini *minishell, char **env);
t_err					verif_required_env(t_mini *shell, t_listenv **tmp);
t_err					exchange_directory(char *dir, t_mini *shell, int opt);
int						exec_command(t_mini *s, t_lst_tkn **lst);
int						go_for_fork(t_mini *m, char **t, t_listenv **x);
t_err					add_slash_to_tab_env(char **tabb);
void					remplace_tabb_env(t_mini *shell, char *str, int j);
char					**recup_tab_argv(char *str);
char					**recup_tab_argv_split_from_list(t_mini *s, \
						t_lst_tkn **l);
void					recup_nb_arg(t_mini *shell, char **tabb);
int						modifie_absolute_path(t_mini *sh, char *s, \
						t_listenv **list, char **tabb);
char					**transfere_list_to_tab(char **tabb, \
						t_listenv **list, int i);
void					count_nb_mail(t_mini *shell, int i, t_listenv **lst);
void					delete_on_list_env(t_mini *s, t_listenv **lst, char *c);
int						verif_all_param(char *str);
int						add_on_list_env(t_mini *s, t_listenv **l, \
						char *str, int c);
char					**realloc_tabb(t_mini *shell, int *i, int j, int x);
t_err					add_arg_heredoc(t_listenv **lst, t_lst_tkn **list);
int						tokenize_tab_semico(t_mini *s, t_listenv **l, \
						char *buff);
void					ft_print_list(t_listenv **l);
t_err					create_project_base(t_mini *s, t_le *ledit, char **env);
t_err					check_error_return(int b, t_mini *shell, t_le *ledit);
int						transfere_list(t_listenv **final, t_list_eof **tmp);
t_err					edit_file_histo(t_mini *shell, t_le *ledit);
int						open_file(char *str, int flags);
t_err					initialize_list_histo(t_mini *s, t_le *ledit, \
						t_listhisto **lst);
int						go_read_and_stock(t_le *ledit, t_mini *shell, int ret);
t_err					touch_tab(t_mini *shell, t_le *ledit, int i);
void					print_possibility_completion(t_mini *shell, \
						t_le *ledit, char *str, int pos);

/*EXPANSION*/
int						transforme_expansion(t_mini *s, t_le *ledit, int *i);
void					inser_on_buffer(t_le *ledit, char *str);
int						browse_dollar_diez(t_listenv **l, t_le *ledit, int *i);
int						browse_param(t_mini *shell, t_le *ledit, int *i);
int						simple_dollar(t_listenv **lst, t_le *ledit, \
						int *i, int exist);
int						dollar_union(t_mini *s, t_le *ledit, int *i, int exist);
int						dollar_equal(t_mini *s, t_le *ledit, int *i, int exist);
int						dollar_query(t_mini *s, t_le *ledit, int *i, int exist);
int						dollar_add(t_mini *s, t_le *ledit, int *i, int exist);
int						dollar_percent(t_mini *s, t_le *ledit, int *i, int on);
int						dollar_double_percent(t_mini *s, t_le *ledit, \
						int *i, int exist);
int						dollar_diez(t_mini *s, t_le *ledit, int *i, int exist);
int						dollar_double_diez(t_mini *s, t_le *ledit, \
						int *i, int exist);
int						if_param_exist(t_listenv **ls, char *buf, int i, int j);
int						last_brace_simple_dollar(t_mini *s, t_le *ledit, \
						int *i, int exist);
int						transforme_tilde(t_mini *shell, t_le *ledit, int *i);
t_err					recup_home(t_mini *minishell, char **str);
t_err					recup_old_pwd(t_mini *minishell, char **str);
t_err					check_same_var_env(t_listenv **copy, char *str, int j);
int						set_or_not(t_listenv **lst, char *to_find, int int_or_str, char **copy);
t_err					cd_get_fullpath(t_mini *shell, char *dir, char **fullpath);
t_err					check_good_path(t_mini *shell, char **tabb, int i, int j);
int						exec_ast_node(t_mini *shell, t_listenv **list_env, char **tab_arg);
int						stock_arg_for_cmd(t_mini *shell, char *str, int size, t_comp **comp);
int						stock_var_set(t_listenv **lst, char *str, int size, t_comp **comp);
char					*str_keep_until_equal(char *str);

// built alias 

int						pars_alias_options(char **args, int *i, int *opt, int j);
int						pars_alias_args(t_ht **h_alias, char **args, int i);
int						pars_unalias_options(char **args, int *i, int *opt, int j);
int						pars_unalias_args(t_ht **h_alias, char **args, int i);
int						replace_alias(t_mini *shell, t_lst_tkn *lst);
#endif
