/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_jobs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:18:56 by ljoly             #+#    #+#             */
/*   Updated: 2019/04/01 19:08:21 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"

/*
** Allocates a new job and returns a pointer to it
*/

t_job			*add_job(t_job **jobs, char *name, int pid)
{
	t_job		*new;
	t_job		*tmp;

	if (!(new = (t_job*)ft_memalloc(sizeof(t_job))))
		return (NULL);
	new->pid = pid;
	new->name = name;
	new->status = 1;
	new->previous_status = 1;
	if (!*jobs)
	{
		new->index = 1;
		*jobs = new;
	}
	else
	{
		tmp = *jobs;
		while (tmp->next)
			tmp = tmp->next;
		new->index = tmp->index + 1;
		new->prev = tmp;
		tmp->next = new;
	}
	ft_printf("[%d] %d\n", new->index, new->pid);
	return (new);
}

/*
** Deletes a job
*/

void			delete_job(t_job *job)
{
	if (job->prev)
	{
		if (job->next)
		{
			job->next->prev = job->prev;
		}
		else
		{
			job->prev->next = NULL;
		}
	}
	if (job->next)
	{
		if (job->prev)
		{
			job->prev->next = job->next;
		}
		else
		{
			job->next->prev = NULL;
		}
	}
	free(job->name);
	free(job);
}

void			print_job(t_job *job, char *status, int term_sig)
{
	if (term_sig && ft_strequ("Terminated: ", status))
	{
		ft_printf("[%d]   %s%-12d%s\n", job->index, status, term_sig,
			job->name);
	}
	else if (term_sig)
	{
		ft_printf("[%d]   %s%-15d%s\n", job->index, status, term_sig,
			job->name);
	}
	else
	{
		ft_printf("[%d]   %-24s%s\n", job->index, status, job->name);
	}
}

static t_bool	(*g_statuses[5])(t_job **jobs, t_job *job,
t_bool display_all) = {
	is_signaled,
	is_exited,
	is_running,
	is_stopped,
	is_continued,
};

/*
** Checks and updates jobs according to their status
*/

void			handle_jobs(t_job **jobs, t_bool display_all)
{
	t_job			*job;
	unsigned long	i;
	int				w;

	if (!*jobs)
		return ;
	job = *jobs;
	while (job)
	{
		w = waitpid(job->pid, &job->status, WNOHANG | WUNTRACED);
		i = 1;
		if (w)
		{
			i = 0;
		}
		while (i < sizeof(g_statuses) / sizeof(*g_statuses))
		{
			if (g_statuses[i](jobs, job, display_all))
			{
				break ;
			}
			i++;
		}
		job = job->next;
	}
}
