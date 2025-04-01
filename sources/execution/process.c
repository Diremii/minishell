/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:14:39 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/01 18:52:41 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_cmd(t_data *data, t_cmd **cmd)
{
	//static char	*cmd_list[7] = {"echo", "cd", "pwd", "export", 
	//				"unset", "env", "exit"};
	static char	*infile = NULL;
	static char	*outfile = NULL;
	static int	here_doc = 0;
	
	if (!(*cmd)->prev)
	{
		infile = (*cmd)->infile;
		outfile = (*cmd)->outfile;
		here_doc = (*cmd)->here_doc;
	}
	if (ft_strcmp((*cmd)->infile, infile) || ft_strcmp((*cmd)->outfile, outfile)
		|| (*cmd)->here_doc != here_doc)
	{
		pipe_in_pipe(data, cmd);
		return (1);
	}
	return (0);
}

void	child_process(int p_fd[2], int fd[2], t_data *data, t_cmd **cmd)
{
	if ((fd[0] == -1 && !(*cmd)->prev))
	{
		close_fd(p_fd);
		close_fd(fd);
		cmd_clear(&data->cmd);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(p_fd[0]);
		if (dup2(p_fd[1], 1) == -1)
			close_all(p_fd, fd, &data->cmd);
		close(p_fd[1]);
		if (check_cmd(data, cmd))
			return ;
		ft_exec(p_fd, fd, data, cmd);
	}
}

void	parent_process(int p_fd[2], int fd[2], t_data *data)
{
	close(p_fd[1]);
	if (dup2(p_fd[0], 0) == -1)
		close_all(p_fd, fd, &data->cmd);
	close(p_fd[0]);
}

pid_t	last_process(int p_fd[2], int fd[2], t_data *data, t_cmd **cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		close_all(p_fd, fd, cmd);
	if (pid == 0)
	{
		if (fd[1] == -1)
		{
			close_fd(p_fd);
			cmd_clear(&data->cmd);
			exit(EXIT_FAILURE);
		}
		else
		{
			if (dup2(fd[1], 1))
				close_all(p_fd, fd, &data->cmd);
			close(fd[1]);
			ft_exec(p_fd, fd, data, cmd);
		}
	}
	else
		close(0);
	return (pid);
}
