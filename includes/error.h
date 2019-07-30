/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 17:32:15 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/31 18:14:20 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum	e_err
{
	EXIT_LR = -99,
	MALLOC_FAIL,
	ERROR_CHARAC,
	TERMCAPS,
	CTRL_D,
	EXIT_ARG,
	OPEN_FAIL,
	USAGE,
	UNKNOW_CHAR,
	EMPTY_BUFF,
	JOB_NOT_FOUND,
	SUCCESS = 0,
}				t_err;

void			error_cmd(int c);
int				put_env_illegal_options(char **tabb, int i);
int				error_no_arg_with_unset();
int				print_error_write_equal_env(char **tabb, int options, int i);
int				ft_print_error_set(char *str, int i);
int				check_nb_arg(int i);
int				check_nb_arg_unset(int nb_arg);
int				print_error_illegal_options(void);
int				error_command_not_found(char *str);
int				error_unset(void);
int				unexpected_token(char *str);
int				ft_print_error_heredoc(char c);
int				print_fail_open(char *file);
int				bad_use(char c);
int				bad_charac(char c);
int				bracket_error(void);
int				error_exclamation(void);
void			param_null_not_set(char *str);
void			param_null_with_arg(char *param, char *value);
int				error_not_found(void);
int				ambiguous_redirect(void);
int				invalid_opt_cd(char opt);
int				check_access(char *dir);
int				error_options_alias(char *func, char error, char opt);
int				error_not_found_alias(char *func, char *error);
int				error_alias_use_alias_unalias(char *func, char *error);
#endif
