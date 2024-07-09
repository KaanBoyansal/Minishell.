/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyansa <mboyansa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:54:43 by mboyansa          #+#    #+#             */
/*   Updated: 2023/10/30 14:38:41 by mboyansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redir_pipe2(void)
{
	t_ink_list	*tmp;

	tmp = g_var.lst;
	if (tmp)
		if (tmp->content[0] == '|')
			return (redir_pipe_helper());
	while (tmp)
	{
		if (tmp->flag == '|')
		{
			if (tmp->next != NULL)
			{
				if (tmp->next->flag == '>' || tmp->next->flag == '<')
					return (redir_pipe_helper());
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redir_pipe(void)
{
	t_ink_list	*tmp;

	tmp = g_var.lst;
	while (tmp)
	{
		if (tmp->flag == '>' || tmp->flag == '<')
			if (tmp->next == NULL)
				return (redir_pipe_helper());
		if (tmp->content[0] == '>' || tmp->content[0] == '<')
			if (tmp->next->content[0] == '|')
				return (redir_pipe_helper());
		if (tmp->content[0] == '>' && tmp->content[1] == '>')
			if (tmp->next == NULL)
				return (redir_pipe_helper());
		if (tmp->content[0] == '<' && tmp->content[1] == '<')
			if (tmp->next == NULL)
				return (redir_pipe_helper());
		if (tmp->content[0] != 0 && tmp->next != NULL)
			if (tmp->next->content[0] == '|' && tmp->content[0] == '|')
				return (redir_pipe_helper());
		tmp = tmp->next;
	}
	return (0);
}

int	minishell_init(char *shell_input)
{
	add_history(shell_input);
	if (check_quote(shell_input))
	{
		free(shell_input);
		return (1);
	}
	start_parser(shell_input);
	if (redir_pipe() || redir_pipe2())
	{
		free(shell_input);
		return (2);
	}
	command_prepare();
	rdirection_flag();
	if (cmd_init())
	{
		all_free2(shell_input);
		return (-1);
	}
	cmd_pipe();
	return (0);
}

int	exec_input(char *shell_input)
{
	if (handle_file() == -1)
	{
		all_free(shell_input);
		return (1);
	}
	if (g_var.str[0] != NULL)
		exec_init();
	all_free(shell_input);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*shell_input;
	int		flag;

	shell_input = NULL;
	first_init(ac, av, env);
	while (1)
	{
		g_var.test = 0;
		shell_input = readline("minishell $ ");
		if (g_var.test)
		{
			free(shell_input);
			continue ;
		}
		if (shell_input == NULL)
		{
			ioctl_helper();
			break ;
		}
		flag = minishell_init(shell_input);
		if (flag == 1 || flag == 2 || flag == -1)
			continue ;
		if (exec_input(shell_input) == 1)
			continue ;
	}
}
