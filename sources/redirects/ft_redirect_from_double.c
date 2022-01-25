/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_from_double.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyuri-go <lyuri-go@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 23:03:18 by lyuri-go          #+#    #+#             */
/*   Updated: 2022/01/25 10:21:21 by lyuri-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_redirect_from_double_init(int fd[2], char *eof, int pid)
{
	char	*line;

	if (pid == 0)
	{
		signal(SIGINT, handle_standard);
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				printf("warning: wanted %s\n", eof);
				break ;
			}
			if (!ft_strncmp(eof, line, ft_strlen(eof))
				&& ft_strlen(eof) == ft_strlen(line))
				break ;
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		}
		close(fd[1]);
	}
}

static void	ft_redirect_from_double_middle(char *eof, int pid)
{
	char	*line;

	if (pid == 0)
	{
		signal(SIGINT, handle_standard);
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				printf("warning: wanted %s\n", eof);
				break ;
			}
			if (!ft_strncmp(eof, line, ft_strlen(eof))
				&& ft_strlen(eof) == ft_strlen(line))
				break ;
		}
	}
}

static void	ft_redi_from_doub_last(t_exec *ex_inf, int fd[2], int pid, int fdt)
{
	if (pid == 0)
	{
		signal(SIGINT, handle_standard);
		if (fdt >= 0)
		{
			dup2(fdt, STDOUT_FILENO);
			close(fdt);
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		ft_execute_cmd(ex_inf, 0);
	}
	close(fd[0]);
	close(fd[1]);
	if (fdt >= 0)
		close(fdt);
	waitpid(pid, NULL, 0);
}

void	ft_redirect_from_double(t_exec *exec_info, int i)
{
	int	fd[2];
	int	pid;
	int	commands;
	int	fd_to[2];

	commands = i;
	signal(SIGINT, handle_nothing);
	pipe(fd);
	pipe(fd_to);
	pid = fork();
	while (exec_info[++commands].next_type == REDIRECT_FROM_DOUBLE)
		ft_redirect_from_double_middle(exec_info[commands].cmd, pid);
	ft_redirect_from_double_init(fd, exec_info[commands].cmd, pid);
	if (exec_info[commands].next_type != LAST)
	{
		ft_redi_from_doub_last(&(exec_info[i]), fd, pid, fd_to[1]);
		ft_signals();
		ft_redirects(exec_info, commands + 1, fd_to[0], -1);
	}
	else
	{
		ft_redi_from_doub_last(&(exec_info[i]), fd, pid, -1);
		ft_signals();
		close(fd_to[0]);
	}
}
