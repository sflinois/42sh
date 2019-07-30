/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lineedit.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 18:52:59 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 19:41:00 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LINEEDIT_H
# define FT_LINEEDIT_H
# include <sys/types.h>
# include <dirent.h>
# include <stdlib.h>
# include "libft.h"
# include "ft_term_caps.h"

# define MAX_KEY_LEN 6

# define KEY_CODE_UP "\x1b\x5b\x41\0\0\0"
# define KEY_CODE_DO "\x1b\x5b\x42\0\0\0"
# define KEY_CODE_RI "\x1b\x5b\x43\0\0\0"
# define KEY_CODE_LE "\x1b\x5b\x44\0\0\0"

# define KEY_CODE_HOME "\x1b\x5b\x48\0\0\0"
# define KEY_CODE_END "\x1b\x5b\x46\0\0\0"

# define KEY_CODE_OPUP "\x1b\x5b\x31\x3b\x35\x41"
# define KEY_CODE_OPDO "\x1b\x5b\x31\x3b\x35\x42"
# define KEY_CODE_OPRI "\x1b\x66\0\0\0\0"
# define KEY_CODE_OPLE "\x1b\x62\0\0\0\0"

# define KEY_CODE_SLE "\x1b\x5b\x31\x3b\x32\x44"
# define KEY_CODE_SRI "\x1b\x5b\x31\x3b\x32\x43"

# define KEY_CODE_CLE "\xc\0\0\0\0\0"

# define F_BLU "\x1B[34m"
# define F_MAG "\x1B[35m"
# define F_CYN "\x1B[36m"
# define F_BLK "\x1b[30m"
# define RESET "\033[0m"

typedef struct			s_listhisto
{
	char				*line;
	struct s_listhisto	*next;
	struct s_listhisto	*prev;
}						t_listhisto;

typedef struct			s_completion
{
	char				*line;
	int					len_line;
	int					max_len;
	int					nb_mail;
	int					in_dir;
	char				*color;
	struct s_completion	*next;
	struct s_completion *prev;
}						t_comp;

typedef struct			s_listeof
{
	char				*str_arg;
	struct s_listeof	*next;
}						t_list_eof;

typedef struct			s_ledit
{
	char				buffer[2048];
	int					prompt;
	int					size_prompt;
	int					i_return;
	int					index_buffer;
	int					save_index_select;
	int					copy_index;
	int					sens_select;
	char				*str_opt_c;
	int					limits_back_x;
	int					nb_break_line;
	int					c_del;
	int					nb_inhib_miss;
	int					index_histo;
	char				*line_loading;
	int					save_line_loading;
	int					histo_on;
	int					start_cut;
	t_list_eof			*list_heredoc;
	t_listhisto			*list_histo;
}						t_le;

typedef struct			s_key_match
{
	char				*key_code;
	int					(*fct)(t_le *ledit);
}						t_key_match;

typedef struct			s_pr_built
{
	char				*arg_built;
}						t_pr_built;

void					free_list_prev(t_le *ledit);
int						initialize_keyboard(void);
int						reinitialize_keyboard();
int						reinitialize_var(t_le *ledit, int buffer);
int						stock_line_for_histo(t_le *ledit, t_listhisto **lst, \
						char *str);
int						copy_buffer_loading(t_le *ledit);
void					list_to_the_end(t_le *ledit);
int						touch_copy(t_le *ledit);
int						touch_paste(t_le *ledit);
int						touch_del_character(t_le *ledit);
int						opt_right(t_le *ledit);
int						opt_left(t_le *ledit);
int						opt_up(t_le *ledit);
int						opt_down(t_le *ledit);
int						top_arrow_print_history(t_le *ledit);
int						down_arrow_print_history(t_le *ledit);
int						left_arrow_move_cursor(t_le *ledit);
int						right_arrow_move_cursor(t_le *ledit);
int						touch_home(t_le *ledit);
int						touch_end(t_le *ledit);
int						touch_shift_left_arrow(t_le *ledit);
int						touch_shift_right_arrow(t_le *ledit);
int						go_clean_screen(t_le *ledit);
int						print_character(t_le *ledit, char *buf);
void					rewrite_buffer(t_le *ledit);
void					putstr_with_prompt(int i_return, char *str);
int						check_if_line_break(t_le *ledit);
void					recup_the_limits_back(t_le *ledit);
void					move_cursor_to_the_end(t_le *ledit);
void					move_cursor_to_the_start(t_le *ledit);
void					move_cursor_fifteen_right();
void					print_my_prompt(t_le *ledit);
int						md_canon_print_prompt(t_le *ledit);
void					free_struct_ledit(t_le *ledit);
int						pars_final_string(t_le *ledit);
t_bool					check_quote_close(char *str, int *i);
t_bool					if_echap_and(char *str, int i, int c);
int						parse_syntax_string(t_le *ledit);
int						grab_dollar(t_le *ledit, char *str, int *i, int ret);
int						parse_brace(t_le *ledit, char *str, int *i);
int						check_possibility_expansion(t_le *ledit, char *str, int *i);
int						parse_and_pipe(char *str, int i, char f);
void					cut_expansion_dollar(t_le *ledit, int *i);
int						recup_first_arg(t_le *ledit, char **tmp, int *i);
void					delete_charac_on_buffer(t_le *ledit);
int						del_on_buffer(t_le *ledit);
int						verif_heredoc(t_le *ledit, char *str, int i);
int						get_arg_heredoc(char *str, t_le *ledit, int i);
int						get_end_heredoc(t_le *ledit, char *str, char *eof, char **strim);
int						nb_heredoc_parse(t_list_eof **lst);
int						create_list_heredoc(char *str, t_le *ledit);
void					free_list_heredoc(t_list_eof **to_free);
int						check_charac_after_redir(char *str, int i, char c);
int						parse_string_after_heredoc(char *str, int i);
int						recup_history(t_le *ledit, int i);
int						ctrl_r_histo(t_le *ledit);
int						touch_del_buf_search(char *buffer, int *index, \
						int i, int nb_co);
int						inser_char_buf_search(char *buff, int *i, char *inser);
int						check_on_list_compare(t_listhisto **lst, t_le *ledit, int i, int j);
int						copy_line_hist_front(t_listhisto **lst, t_le *ledit, int j);
int						copy_line_hist_back(t_listhisto **lst, t_le *ledit, int j);
t_bool					verif_miss_inhib(char *str, int i);
t_bool					parse_full_backslashn(char *str);
int						check_if_semico(char *str);
int						buffer_in_one_line(char *str);
int						recup_last_command(t_le *ledit, int i);
int						add_to_list_completion(t_comp **comp, char *str);
void					print_lst_comp(t_comp *comp);
void					print_lst_mode_select(t_le *ledit, t_comp *comp, int index);
void					free_list_completion(t_comp **comp);
int						define_arg(t_le *ledit, char *buffer, int *pos, char **str);
int						print_possibility_comp(t_le *ledit, t_comp **comp, int len_s);
int						stock_binary(char *dir, char *str, int size, t_comp **comp);
int						check_mode_copy(t_le *ledit, char *buf);
void					get_position_cursor(int *rows, int i);
int						nb_arg_in_one_line(int max_len);
int						completion_with_choise_or_not(t_le *ledit, int rows, t_comp *comp);
int						add_color_file(t_comp *comp, char *dir, int *ret);
#endif
