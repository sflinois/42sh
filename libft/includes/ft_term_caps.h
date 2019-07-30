/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_caps.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:58:12 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/11/08 17:35:41 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TERM_CAPS_H
# define FT_TERM_CAPS_H

#include <term.h>

void						ft_tc_clear_after_cursor(void);
void						ft_tc_del_the_carac(void);
void						ft_tc_down_cursor(void);
void						ft_tc_end_select_mode(void);
void						ft_tc_move_cursor_left(void);
void						ft_tc_move_cursor_one_right(void);
int							ft_tc_my_outc(int c);
void						ft_tc_restaure_position_cursor(void);
void						ft_tc_save_position_cursor(void);
void						ft_tc_select_mode(void);
void						ft_tc_up_cursor_one_line(void);
void						ft_tc_clean_screen(void);
void						ft_tc_clean_line_aft_cursor(void);
#endif
