/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 14:45:46 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/29 17:09:25 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEXER_H
# define FT_LEXER_H
# include "libft.h"

# define T_COMMAND		1
# define T_FILE			2
# define T_REDI_R		3
# define T_REDI_RR		4
# define T_REDI_L		5
# define T_REDI_LL		6
# define T_REDI_LR		7
# define T_PIPE			8
# define T_OR			9
# define T_AND			10
# define T_BACKQU		11
# define T_BLANK		12
# define T_DQUOTE		13
# define T_SQUOTE		14
# define T_BQUOTE		15
# define T_SEMICO		16
# define T_END			17
# define T_JOB			18
# define T_ERROR		99

typedef struct			s_redir
{
	int					i_out;
	int					i_in;
	char				*out;
	char				*in;
	char				*arg_heredoc;
}						t_redir;

typedef struct			s_token
{
	int					nb_order;
	char				*order;
	struct s_redir		redir;
	struct s_token		*next;
}						t_lst_tkn;

typedef struct			s_var_redir
{
	int					a;
	int					chain;
	int					t_redi;
	char				*file;
	char				*arg_redir;
}						t_vred;

typedef struct			s_tablex
{
	char				oper;
	int					(*fct)(char **b, t_lst_tkn **l);
}						t_tablex;

typedef struct			s_tokenizer
{
	int					other;
	char				temp_other[520];
	int					i_oth;
}						t_tknizer;

void					ft_print_list_tkn(t_lst_tkn **lst);
int						add_token_to_list(t_lst_tkn **lst, int t, char *c);
void					free_tkn(t_lst_tkn *tkn);
void					free_list_tkn(t_lst_tkn **lst);
int						handle_space(char **buffer, t_lst_tkn **lst);
int						handle_outredir(char **buffer, t_lst_tkn **lst);
int						handle_inredir(char **buffer, t_lst_tkn **lst);
void					initialize_var_redir(t_vred *vredir);
void					get_number_fd(char **buffer, int *a);
int						get_file_redir(char **buff, int i, char **file);
int						verif_int_std_one(t_lst_tkn *tmp, int a, char *f);
int						verif_int_std_in(t_lst_tkn *tmp, int a, char *f);
int						handle_dquote(char **buffer, t_lst_tkn **lst);
int						handle_semico(char **buffer, t_lst_tkn **lst);
int						handle_squote(char **buffer, t_lst_tkn **lst);
int						handle_bquote(char **buffer, t_lst_tkn **lst);
int						handle_and(char **buffer, t_lst_tkn **lst);
int						handle_pipe(char **buffer, t_lst_tkn **lst);
int						handle_others(char **buffer, t_lst_tkn **lst);
void					free_struct_vred(t_vred *vredir, t_lst_tkn **lst);
int						handle_dquote_redir(char **buff, char **file, char c);
int						recup_others(char **buffer, char **file);
void					define_token_redir(char **buffer, int *t_redi, int i);
int						s_redir(char **arg, char **save_buffer, char **buffer);
#endif
