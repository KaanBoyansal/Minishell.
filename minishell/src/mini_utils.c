/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyansa <mboyansa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:54:38 by mboyansa          #+#    #+#             */
/*   Updated: 2023/10/30 14:09:35 by mboyansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	command_prepare(void)
{
	t_ink_list	*tmp;
	int			i;

	i = 0;
	tmp = g_var.lst;
	g_var.lst_size = link_lstsize(g_var.lst);
	g_var.str = malloc(sizeof(char *) * (g_var.lst_size + 1));
	while (tmp)
	{
		g_var.str[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	g_var.str[i] = NULL;
}

void	env_malloc(char **env)
{
	int	i;
	int	len;

	len = 0;
	while (env[len])
		len++;
	g_var.env_size = len;
	i = 0;
	g_var.env = malloc(sizeof(char *) * (g_var.env_size + 2));
	while (env[i])
	{
		g_var.env[i] = ft_strdup(env[i]);
		i++;
	}
	g_var.env[i] = NULL;
}

void	env_export(char **env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (env[len])
		len++;
	g_var.export_size = len;
	g_var.exports = malloc(sizeof(char *) * (g_var.export_size + 2));
	while (env[i])
	{
		g_var.exports[i] = ft_strdup(env[i]);
		i++;
	}
	g_var.exports[i] = NULL;
}

void	first_init(int ac, char **av, char **env)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	(void)ac;
	(void)av;
	g_var.exit_status = 0;
	g_var.str = NULL;
	g_var.env = NULL;
	g_var.exports = NULL;
	g_var.cmd = NULL;
	g_var.cmds = NULL;
	g_var.pipe = NULL;
	g_var.pid = NULL;
	g_var.help = NULL;
	g_var.path_env = NULL;
	g_var.rdr_left = 1;
	env_malloc(env);
	env_export(env);
}
