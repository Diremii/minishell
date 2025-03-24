/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:11:41 by ttremel           #+#    #+#             */
/*   Updated: 2025/03/24 16:43:10 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

static int	create_here_doc(int fd, char **av)
{
	size_t	lim_size;
	char	*line;

	line = NULL;
	lim_size = ft_strlen(av[1]);
	while (1)
	{
		ft_printf_fd("here_doc> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			close(fd);
			return (-1);
		}
		line[ft_strlen(line) - 1] = 0;
		if (ft_strncmp(av[1], line, lim_size + 1) == 0)
			break ;
		ft_printf_fd("%s\n", fd, line);
		free(line);
	}
	free(line);
	return (0);
}

int	here_doc(char **av)
{
	int		fd[2];
	char	*file;
	int		rand_num;

	file = "./.nfs0000000000";
	fd[0] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd[0] == -1)
		return (-1);
	if (create_here_doc(fd[0], av) == -1)
		return (-1);
	close(fd[0]);
	fd[1] = open(file, O_RDONLY, 0777);
	if (fd[1] == -1)
		return (-1);
	unlink(file);
	return (fd[1]);
}

static int	open_fd(int fd[2], char **av, char ac, int h_doc)
{
	int		ret;

	if (h_doc)
		ret = here_doc(av);
	else
		ret = open(av[0], O_RDONLY, 0777);
	fd[0] = ret;
	if (h_doc)
		ret = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		ret = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	fd[1] = ret;
	return (0);
}

/*
arguments needed : 
- ac  : size list of list of char,
- av  : list of cmds with infile and outfile : 
    	[infile "cmd1" ... "cmdn" outfile],
		[here_doc LIMITER "cmd1" ... "cmdn" outfile]
- env : the environement of the OS
description :
create pipe
*/
int	ft_pipe(int ac, char **av, char *env)
{
	t_cmd	**cmds;
	pid_t	pid;
	int		fd[2];
	int		here_doc;

	here_doc = (ft_strcmp(av[1], "here_doc") == 0);
	if (ac < 4 || (ac < 5 && here_doc))
		error_handler(0, NULL);
	cmds = parser(&av[2 + here_doc], (ac - (3 + here_doc)), env);
	if (!cmds)
		return (1);
	cmds[0]->in_file = ft_strdup(av[1]);
	cmds[0]->out_file = ft_strdup(av[ac - 1]);
	if (!(*cmds)->in_file || !(*cmds)->out_file
		|| open_fd(fd, &av[1], ac - 1, here_doc) == -1)
	{
		free_for_all(cmds);
		return (-1);
	}
	pid = pipex((ac - (2 + here_doc)), cmds, fd, here_doc);
	close_fd(fd);
	free_for_all(cmds);
	wait_all_pid(pid, ac - (2 + here_doc));
}
