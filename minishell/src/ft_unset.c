/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyansa <mboyansa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:54:17 by mboyansa          #+#    #+#             */
/*   Updated: 2023/10/30 14:09:35 by mboyansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	equ_env(char *str)
{
	int	i;

	i = 0;
	while (g_var.env[i])
	{
		if (len_equal(g_var.env[i]) == len_equal(str))
		{
			if (!ft_strncmpv2(g_var.env[i], str, len_equal(g_var.env[i])))
				return (i);
		}
		i++;
	}
	return (-1);
}

int	equ_export(char *str)
{
	int	i;

	i = 0;
	while (g_var.exports[i])
	{
		if (len_equal(g_var.exports[i]) == len_equal(str))
		{
			if (!ft_strncmpv2(g_var.exports[i],
					str, len_equal(g_var.exports[i])))
				return (i);
		}
		i++;
	}
	return (-1);
}

void	delenv(char *str)
{
	int		index;
	int		len;
	int		i;
	int		j;
	char	**temp;

	index = equ_env(str);
	if (index == -1)
		return ;
	len = splt_len(g_var.env);
	temp = malloc(sizeof(char *) * (len + 1));
	i = -1;
	j = -1;
	while (++i < len)
	{
		if (i == index)
			j++;
		temp[i] = ft_strdup(g_var.env[++j]);
	}
	temp[i] = 0;
	free_func(g_var.env);
	g_var.env = temp;
}

void	delexport(char *str)
{
	int		index;
	int		len;
	int		i;
	int		j;
	char	**temp;

	index = equ_export(str);
	if (index == -1)
		return ;
	len = splt_len(g_var.exports);
	temp = malloc(sizeof(char *) * (len + 1));
	i = -1;
	j = -1;
	while (++i < len)
	{
		if (i == index)
			j++;
		temp[i] = ft_strdup(g_var.exports[++j]);
	}
	temp[i] = 0;
	free_func(g_var.exports);
	g_var.exports = temp;
}

void	ft_unset(void)
{
	int	len;
	int	i;

	len = splt_len(g_var.cmds[0]->str);
	i = 1;
	while (i < len)
	{
		g_var.path_flag = strequal(g_var.cmds[0]->str[i], "PATH");
		delexport(g_var.cmds[0]->str[i]);
		delenv(g_var.cmds[0]->str[i]);
		i++;
	}
}
