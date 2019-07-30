/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:50:44 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 17:48:27 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "ft_minishell.h"

static int	return_final_string(t_le *ledit, t_mini *shell, int ret)
{
	int		i;
	int		other_ret;

	i = 0;
	if ((buffer_in_one_line(ledit->buffer)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if ((stock_line_for_histo(ledit, &ledit->list_histo, ledit->buffer)) \
			== MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (ret == 1)
	{
		if ((other_ret = transforme_expansion(shell, ledit, &i)) < 0)
		{
			reinitialize_var(ledit, 0);
			ft_bzero(&ledit->buffer, sizeof(char) * 2048);
			if (other_ret == EMPTY_BUFF)
				return (0);
			return (other_ret);
		}
	}
	reinitialize_var(ledit, 0);
	if (ret != 1)
		ft_bzero(ledit->buffer, sizeof(char) * 2048);
	return (ret);
}

int			go_to_histo(t_le *ledit, int index_histo)
{
	if (index_histo == -1)
		return (0);
	else
	{
		while (index_histo != 0)
		{
			index_histo--;
			top_arrow_print_history(ledit);
		}
		top_arrow_print_history(ledit);
	}
	return (0);
}

static int	know_wchich_charac_is(t_le *ledit, char *buf)
{
	int							i;
	static struct s_key_match	tab_key[13] = {
		{KEY_CODE_LE, &left_arrow_move_cursor},
		{KEY_CODE_RI, &right_arrow_move_cursor},
		{KEY_CODE_UP, &top_arrow_print_history},
		{KEY_CODE_DO, &down_arrow_print_history},
		{KEY_CODE_HOME, &touch_home},
		{KEY_CODE_END, &touch_end},
		{KEY_CODE_SLE, &touch_shift_left_arrow},
		{KEY_CODE_SRI, &touch_shift_right_arrow},
		{KEY_CODE_CLE, &go_clean_screen},
		{KEY_CODE_OPLE, &opt_left},
		{KEY_CODE_OPRI, &opt_right},
		{KEY_CODE_OPUP, &opt_up},
		{KEY_CODE_OPDO, &opt_down}
	};

	i = 0;
	while (i < 13)
		if (ft_memcmp(buf, tab_key[i++].key_code, MAX_KEY_LEN) == 0)
			return (tab_key[i - 1].fct(ledit));
	if (buf[0] >= 32 && buf[0] <= 126 && buf[1] == 0)
		return (print_character(ledit, buf));
	return (-1);
}

static int	check_special_enter(t_mini *shell, t_le *ledit, char *buf)
{
	if (buf[0] == 127)
		return (touch_del_character(ledit));
	else if (buf[0] == -30 && buf[1] == -120)
		return (touch_paste(ledit));
	else if (buf[0] == 9 && buf[1] == 0)
		return (touch_tab(shell, ledit, 0));
	// else if (buf[0] == 26 && buf[1] == 0)
	// 	stop_job ctrl z
	// else if (buf[0] == 25 && buf[1] == 0)
	// 	ctrl y
	else if (buf[0] == 3)
	{
		reinitialize_var(ledit, 0);
		return (-2);
	}
	else if (buf[0] == 18)
	{
		list_to_the_end(ledit);
		go_to_histo(ledit, ctrl_r_histo(ledit));
	}
	else
	{
		reinitialize_var(ledit, 1);
		return (UNKNOW_CHAR);
	}
	return (0);
}

int			go_read_and_stock(t_le *ledit, t_mini *shell, int ret)
{
	char	buf[6];

	ft_bzero(buf, sizeof(char) * 6);
	if (((ret = read(0, buf, 6)) == 1 && buf[0] == 4) || ret < 0)
		return (CTRL_D);
	else if (buf[0] == 10)
	{
		if ((ret = pars_final_string(ledit)) != 0)
			return (return_final_string(ledit, shell, ret));
		handle_jobs(&shell->jobs, FALSE);
	}
	else
	{
		// ft_printf("buf0 -> %d buf1 -> %d buf2 -> %d, buf3-> %d, buf->4 %d, buf5-> %d\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
		if (check_mode_copy(ledit, buf) == 1)
			return (0);
		if ((ret = know_wchich_charac_is(ledit, buf)) == -1)
			return (check_special_enter(shell, ledit, buf));
		return (ret);
	}
	return (0);
}
