/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:07:16 by ljoly             #+#    #+#             */
/*   Updated: 2019/04/01 17:25:40 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBS_H
# define JOBS_H

#include "libft.h"
#include "error.h"

typedef struct	s_job
{
	int				pid;
	int				index;
	char			*name;
	int				previous_status;
	int				status;
	struct s_job	*prev;
	struct s_job	*next;
}				t_job;

void			handle_jobs(t_job **jobs, t_bool display_all);
t_job			*add_job(t_job **jobs, char *name, int pid);
void			delete_job(t_job *job);

t_bool			is_signaled(t_job **jobs, t_job *job, t_bool display_all);
t_bool			is_running(t_job **jobs, t_job *job, t_bool display_all);
t_bool			is_stopped(t_job **jobs, t_job *job, t_bool display_all);
t_bool			is_exited(t_job **jobs, t_job *job, t_bool display_all);
t_bool			is_continued(t_job **jobs, t_job *job, t_bool display_all);

void			print_job(t_job *job, char *status, int term_sig);

#endif
