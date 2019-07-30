/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_statuses.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:14:36 by ljoly             #+#    #+#             */
/*   Updated: 2019/04/01 19:09:10 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"

t_bool		is_signaled(t_job **jobs, t_job *job, t_bool display_all)
{
	(void)jobs;
	(void)display_all;
	if (WIFSIGNALED(job->status))
	{
		if (job->previous_status == 1)
		{
			job->previous_status = job->status;
		}
		else
		{
			print_job(job, "Terminated: ", WTERMSIG(job->status));
			if (job == *jobs)
			{
				*jobs = (*jobs)->next;
			}
			delete_job(job);
		}
		return (TRUE);
	}
	return (FALSE);
}

t_bool		is_running(t_job **jobs, t_job *job, t_bool display_all)
{
	(void)jobs;
	if (display_all && WIFSIGNALED(job->status))
	{
		print_job(job, "Running", 0);
		job->previous_status = job->status;
		return (TRUE);
	}
	return (FALSE);
}

t_bool		is_stopped(t_job **jobs, t_job *job, t_bool display_all)
{
	(void)jobs;
	if ((job->previous_status != job->status
		|| display_all) && WIFSTOPPED(job->status))
	{
		print_job(job, "Stopped: ", WSTOPSIG(job->status));
		job->previous_status = job->status;
		return (TRUE);
	}
	return (FALSE);
}

t_bool		is_continued(t_job **jobs, t_job *job, t_bool display_all)
{
	(void)jobs;
	(void)display_all;
	if (WIFCONTINUED(job->status))
	{
		ft_putendl("CONTINUE");
		job->status = 1;
		return (TRUE);
	}
	return (FALSE);
}

t_bool		is_exited(t_job **jobs, t_job *job, t_bool display_all)
{
	(void)display_all;
	if (job->previous_status != job->status && WIFEXITED(job->status))
	{
		print_job(job, "Done", 0);
		if (job == *jobs)
		{
			*jobs = (*jobs)->next;
		}
		delete_job(job);
		return (TRUE);
	}
	return (FALSE);
}
