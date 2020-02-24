/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:19:16 by wpark             #+#    #+#             */
/*   Updated: 2020/02/24 17:19:34 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	check_file_exist(t_cmd *cmd, char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (no_file_error(file, NULL, 0));
	cmd->in->fd = fd;
	return (1);
}

static int
	open_out_file(t_cmd *cmd, char *file, int is_double)
{
	int fd;

	if (is_double)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	else
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	if (fd < 0)
		return (0); // file create error
	if (is_double)
		cmd->out_dbl->fd = fd;
	else
		cmd->out->fd = fd;
	return (1);
}

void
	redirection(t_cmd *cmd)
{
	if (cmd->in && (check_file_exist(cmd, cmd->in->file)))
	{
		cmd->in->save_fd = dup(0); 
		dup2(cmd->in->fd, 0);
		close(cmd->in->fd);
	}
	if (cmd->out && open_out_file(cmd, cmd->out->file, 0))
	{
		cmd->out->save_fd = dup(1);
		dup2(cmd->out->fd, 1);
		close(cmd->out->fd);
	}
	if (cmd->out_dbl && open_out_file(cmd, cmd->out_dbl->file, 1))
	{
		cmd->out_dbl->save_fd = dup(1);
		dup2(cmd->out_dbl->fd, 1);
		close(cmd->out_dbl->fd);
	}
}

void
	close_redirection(t_cmd *cmd)
{
	if (cmd->in)
	{
		dup2(cmd->in->save_fd, 0);
		close(cmd->in->save_fd);
	}
	if (cmd->out)
	{
		dup2(cmd->out->save_fd, 1);
		close(cmd->out->save_fd);
	}
	if (cmd->out_dbl)
	{
		dup2(cmd->out_dbl->save_fd, 1);
		close(cmd->out_dbl->save_fd);
	}
}
