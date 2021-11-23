/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyuri-go <lyuri-go@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 22:30:36 by lyuri-go          #+#    #+#             */
/*   Updated: 2021/11/23 21:34:21 by lyuri-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libs/libft/libft.h"
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>

# define HISTORY_FILE ".minishell_history"

typedef struct s_mini {
	char	**envs;
}	t_mini;

void	ft_execute(char *line);
void	ft_signals(void);
void	ft_load_history(void);
void	ft_add_history(char *in);

void	ft_pwd(void);

char	*ft_get_env(char *env);
t_mini	*mini_s(void);

#endif
