/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyansa <mboyansa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:03:30 by mboyansa          #+#    #+#             */
/*   Updated: 2023/10/30 14:42:00 by mboyansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	path_splt(void)
{
	int		i;
	char	**str;
	char	*find;

	g_var.path_env = NULL;
	if (g_var.path_flag == 1)
		return (0);
	find = find_in_env("PATH");
	if (find == NULL)
		return (1);
	i = 0;
	str = ft_split(find + 5, ':');
	g_var.path_env = malloc(sizeof(char *) * (splt_len(str) + 2));
	while (str[i])
	{
		g_var.path_env[i] = ft_strjoin(str[i], "/");
		free(str[i]);
		i++;
	}
	g_var.path_env[i] = NULL;
	free(str);
	return (0);
}

int	command_build3(int i)
{
	if (strequal(g_var.cmds[i]->str[0], "exit"))
	{
		if (built_control() == 0)
			return (0);
		if (i == 0)
		{
			ft_exit();
			return (0);
		}
	}
	else if (strequal(g_var.cmds[i]->str[0], "export"))
	{
		if (built_control() == 0)
			return (0);
		if (g_var.cmds[i]->str[1])
			ft_export();
		return (1);
	}
	return (1);
}

int	command_build2(int i)
{
	if (strequal(g_var.cmds[i]->str[0], "cd"))
	{
		if (built_control() == 0)
			return (0);
		cd_func(i);
		return (0);
	}
	else if (strequal(g_var.cmds[i]->str[0], "unset"))
	{
		if (built_control() == 0)
			return (0);
		if (g_var.cmds[0]->str[i + 1] != NULL)
			ft_unset();
		else
			return (2);
		return (0);
	}
	else
	{
		if (command_build3(i) == 0)
			return (0);
		else
			return (1);
	}
	return (1);
}

void	export_print(void)
{
	int	i;
	int	k;
	int	flag;

	i = -1;
	while (g_var.exports[++i])
	{
		flag = 0;
		k = -1;
		printf("declare -x ");
		while (g_var.exports[i][++k])
		{
			if (g_var.exports[i][k] == '=')
			{
				printf("%c%c", g_var.exports[i][k++], '"');
				flag = 1;
				printf("%c", g_var.exports[i][k]);
			}
			else
				printf("%c", g_var.exports[i][k]);
		}
		if (flag)
			printf("%c", '"');
		printf("\n");
	}
}

int	command_build(int i)
{
	if (strequal(g_var.cmds[i]->str[0], "echo"))
	{
		ft_echo(i);
		return (0);
	}
	else if (strequal(g_var.cmds[i]->str[0], "env"))
	{
		ft_env();
		return (0);
	}
	else if (strequal(g_var.cmds[i]->str[0], "pwd"))
	{
		ft_pwd();
		return (0);
	}
	else if (strequal(g_var.cmds[i]->str[0], "export"))
	{
		if (g_var.cmds[0]->str[1] == NULL)
			export_print();
		return (0);
	}
	return (1);
}
