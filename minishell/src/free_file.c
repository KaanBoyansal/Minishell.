/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyansa <mboyansa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:53:43 by mboyansa          #+#    #+#             */
/*   Updated: 2023/10/30 14:36:45 by mboyansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	rdirect_add(void)
{
	g_var.rdr_left = 1;
	write(1, "\033[2D", 4);
	write(1, "  ", 2);
	write(1, "\033[2D", 4);
	ioctl(-1, TIOCSTI, "\n");
}

void	all_free_add(char *shell_input)
{
	if (g_var.pipe_count >= 0)
		if (g_var.pipe)
			free(g_var.pipe);
	if (g_var.pid)
		free(g_var.pid);
	g_var.pid = NULL;
	if (g_var.acces)
		free(g_var.acces);
	if (shell_input)
		free(shell_input);
	unlink_func();
}

void	all_free(char *shell_input)
{
	int	i;

	i = -1;
	if (g_var.str)
		free_func(g_var.str);
	while (++i < g_var.pipe_count + 1)
	{
		if (g_var.help[i])
			free_func(g_var.help[i]);
		if (g_var.cmds[i])
			free(g_var.cmds[i]);
	}
	if (g_var.help)
		free(g_var.help);
	if (g_var.cmds)
		free(g_var.cmds);
	i = -1;
	while (++i < g_var.pipe_count)
		if (g_var.pipe[i])
			free(g_var.pipe[i]);
	all_free_add(shell_input);
}

void	all_free_add2(char *shell_input)
{
	int	i;

	i = 0;
	while (++i < g_var.pipe_count)
		if (g_var.pipe[i])
			free(g_var.pipe[i]);
	if (g_var.pipe_count >= 0)
		free(g_var.pipe);
	if (g_var.pid)
		free(g_var.pid);
	g_var.pid = NULL;
	if (shell_input)
		free(shell_input);
}

void	all_free2(char *shell_input)
{
	int	i;

	i = 0;
	if (g_var.str)
		free_func(g_var.str);
	if (g_var.free_control == 0)
	{
		while (i < g_var.pipe_count + 1)
		{
			if (g_var.help[i])
				free_func(g_var.help[i]);
			if (g_var.cmds)
				free(g_var.cmds[i]);
			i++;
		}
		if (g_var.cmds)
			free(g_var.cmds);
		if (g_var.help)
			free(g_var.help);
	}
	all_free_add2(shell_input);
}
