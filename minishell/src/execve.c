/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyansa <mboyansa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:53:23 by mboyansa          #+#    #+#             */
/*   Updated: 2023/10/30 14:32:45 by mboyansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_path(int *flag, int i)
{
	if (path_splt() == 1)
	{
		if (g_var.acces)
			free(g_var.acces);
		g_var.acces = g_var.cmds[i]->str[0];
		if (execve(g_var.acces, g_var.cmds[i]->str, g_var.env) == -1)
		{
			printf("minishell: %s: command not found\n",
				g_var.cmds[i]->str[0]);
			exit(127);
		}
	}
	*flag = cmd_acces(i);
	if (g_var.path_env)
		free_func(g_var.path_env);
}

void	exec_main(int i, int *flag)
{
	if (*flag == 0)
	{
		if (execve(g_var.acces, g_var.cmds[i]->str, g_var.env) == -1)
		{
			printf("minishell: %s: command not found\n",
				g_var.cmds[i]->str[0]);
			exit(127);
		}
	}
	else if (*flag != 1)
	{
		printf("minishell: %s: command not found\n",
			g_var.cmds[i]->str[0]);
		exit(127);
	}
}

void	dup_func(int i)
{
	dup2(g_var.cmds[i]->f_in, STDIN_FILENO);
	dup2(g_var.cmds[i]->f_out, STDOUT_FILENO);
}

void	exec_start(int *flag, int i)
{
	exec_path(flag, i);
	exec_main(i, flag);
}

void	exec_init(void)
{
	int		i;
	int		flag[2];
	int		id;

	i = -1;
	flag[0] = 1;
	id = 0;
	while (g_var.cmds[++i])
	{
		if (command_build2(i) == 1)
		{
			g_var.pid[id] = fork();
			if (g_var.pid[id] == 0)
			{
				close_fd(g_var.cmds[i]);
				dup_func(i);
				if (command_build(i) == 1)
					exec_start(flag, i);
				exit(0);
			}
		}
		id++;
	}
	waitpid_func(id);
}
