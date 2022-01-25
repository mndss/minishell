/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyuri-go <lyuri-go@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 18:13:05 by elima-me          #+#    #+#             */
/*   Updated: 2022/01/25 10:49:38 by lyuri-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_redirects(t_exec *exec_info, int i, int fdi, int fdo)
{
	(void)fdo;
	if (exec_info[i].next_type == PIPE || (exec_info[i].next_type == LAST
			&& exec_info[i - 1].next_type == PIPE))
		ft_pipe(exec_info, i, fdi);
	if (exec_info[i].next_type == REDIRECT_TO_SINGLE
		|| exec_info[i].next_type == REDIRECT_TO_DOUBLE
		|| (exec_info[i].next_type == LAST
			&& exec_info[i - 1].next_type == REDIRECT_TO_SINGLE)
		|| (exec_info[i].next_type == LAST
			&& exec_info[i - 1].next_type == REDIRECT_TO_DOUBLE))
		ft_redirect_to(exec_info, i, fdi);
	if (exec_info[i].next_type == REDIRECT_FROM_SINGLE
		|| (exec_info[i].next_type == LAST
			&& exec_info[i - 1].next_type == REDIRECT_FROM_SINGLE))
		ft_redirect_from_single(exec_info, i);
	if (exec_info[i].next_type == REDIRECT_FROM_DOUBLE
		|| (exec_info[i].next_type == LAST
			&& exec_info[i - 1].next_type == REDIRECT_FROM_DOUBLE))
		ft_redirect_from_double(exec_info, i);
}
