/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elima-me <elima-me@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 22:30:36 by lyuri-go          #+#    #+#             */
/*   Updated: 2021/12/15 19:51:14 by elima-me         ###   ########.fr       */
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

# define HISTORY_FILE "/.minishell_history"

typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
	int				visible;
}	t_env;

enum e_cmd_next_type {
	LAST,
	PIPE,
	REDIRECT_TO_SINGLE,
	REDIRECT_TO_DOUBLE,
	REDIRECT_FROM_SINGLE,
	REDIRECT_FROM_DOUBLE,
};

typedef struct s_exec {
	char	**args;
	char	*cmd;
	int		next_type;
}	t_exec;

typedef struct s_mini {
	t_env	*envs;
	int		last_exec_code;
}	t_mini;

// CONTROLLERS
void	ft_execute(char *line);
void	ft_signals(void);
void	ft_load_history(void);
void	ft_add_history(char *in);
void	ft_free(t_exec *exec);

// CMDS
void	ft_echo(char **argv);
void	ft_pwd(void);
void	ft_exit(t_exec *exec);
void	ft_env(void);
void	ft_export(char **args);
void	ft_unset(char **arg);
void	ft_cd(char **path);

// UTILS
char	*ft_get_env(char *env);
t_env	*ft_new_node(char *key, char *value, int visible);
void	ft_env_add_front(t_env **envs, t_env *new);
t_mini	*mini_s(void);

//PARSERS
void	ft_parser(char *line, t_exec *exec_info);
void	ft_free_parser(t_exec *exec);
void	ft_parse_special(char *line, int *init_arg, t_exec *exec);
char	*ft_substr_clean(char *line, int init_arg, int len);
void	ft_parser_envs(char **envp);
void	ft_free_env(void);
int		split_key(char *env);

#endif
