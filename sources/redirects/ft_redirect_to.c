/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_to.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyuri-go <lyuri-go@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 23:58:26 by elima-me          #+#    #+#             */
/*   Updated: 2022/01/23 12:33:55 by lyuri-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_open(t_exec *exec_info, int i)
{
	int	file;

	if (exec_info[i - 1].next_type == REDIRECT_TO_DOUBLE)
		file = open(exec_info[i].cmd, O_CREAT | O_APPEND | O_RDWR, 0644);
	else if (exec_info[i - 1].next_type == REDIRECT_TO_SINGLE)
		file = open(exec_info[i].cmd, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	return (file);
}

static int	ft_redirect_to_init(t_exec *exec_info, int fd[2], int fdi, int i)
{
	int	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (fdi > 0)
		{
			dup2(fdi, STDIN_FILENO);
			close(fdi);
		}
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		ft_execute_cmd(&(exec_info[i]), 0);
	}
	close(fd[1]);
	return (pid);
}

static void	ft_redirect_to_last(t_exec *exec_info, int fd[2], int i)
{
	char	line;
	int		file;

	file = ft_open(exec_info, i);
	if (!(exec_info[i].next_type == REDIRECT_TO_SINGLE
			|| exec_info[i].next_type == REDIRECT_TO_DOUBLE))
	{
		while (read(fd[0], &line, 1))
			write(file, &line, 1);
		close(file);
		close(fd[0]);
	}
}

void	ft_redirect_to(t_exec *exec_info, int i, int fdi)
{
	static int		fd[2];
	int				pid;

	if (i == 0 || fdi == -2 || (fdi >= 0 && exec_info[i - 2].next_type == PIPE))
		pid = ft_redirect_to_init(exec_info, fd, fdi, i);
	else
	{
		if (fdi >= 0)
			fd[0] = fdi;
		ft_redirect_to_last(exec_info, fd, i);
	}
	if (exec_info[i].next_type == REDIRECT_TO_SINGLE
		|| exec_info[i].next_type == REDIRECT_TO_DOUBLE)
		ft_redirect_to(exec_info, i + 1, -1);
	else if (exec_info[i].next_type != LAST)
		ft_redirects(exec_info, i + 1, -2, -1);
	if (i == 0 || fdi == -2 || (fdi >= 0 && exec_info[i - 2].next_type == PIPE))
		waitpid(pid, NULL, 0);
}
