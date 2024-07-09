/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyansa <mboyansa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:54:55 by mboyansa          #+#    #+#             */
/*   Updated: 2023/10/30 14:27:09 by mboyansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*dollar_handler(char *str, char q)
{
	int		i;
	int		j;
	char	*result;
	char	*env;

	if (q == 39)
		return (str);
	result = NULL;
	i = 0;
	while (str[i])
	{
		j = i;
		while (str[i] && str[i] != '$')
			i++;
		result = ft_strjoin3(result, ft_strdup2(str, j, i));
		if (str[i] == '$')
		{
			dollar_help(str, i);
			env = get_env_var(&str[++i], g_var.env, &i, &j);
			if (env)
				result = ft_strjoin3(result, env);
		}
	}
	free(str);
	return (result);
}

char	*handle_regular(char *str, int *index)
{
	int		i;
	char	*result;

	i = *index;
	while (str[i] && !is_it_special(str[i]) && str[i] != 34 && str[i] != 39)
		i++;
	result = ft_strdup2(str, *index, i);
	*index = i;
	return (result);
}

void	handle_others(char *str, int *index)
{
	int		i;
	char	*result;

	result = NULL;
	i = *index;
	while (str[i] && !is_it_special(str[i]))
	{
		if (str[i] == 34 || str[i] == 39)
		{
			i++;
			result = ft_strjoin3(result, dollar_handler
					(ft_strdup3(str, &i, str[i - 1]), str[i - 1]));
		}
		else
			result = ft_strjoin3(result,
					dollar_handler(handle_regular(str, &i), 0));
	}
	link_lstadd_back(&g_var.lst, link_lstnew(result, 'b'));
	*index = i;
}

void	special_handler(char *str, int *index, char q)
{
	int		backup;
	int		i;
	char	*result;

	backup = *index;
	i = 1;
	if (str[i + backup] == q && str[i + backup] != '|')
		i++;
	result = ft_strdup2(str, backup, i + backup);
	link_lstadd_back(&g_var.lst, link_lstnew(result, q));
	*index = i + backup;
}

int	start_parser(char *str)
{
	int		len;
	int		i;

	len = ft_strlen(str);
	i = 0;
	link_lstclear(&g_var.lst);
	while (i < len)
	{
		while (str[i] == ' ' || str[i] == 9)
			i++;
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			special_handler(str, &i, str[i]);
		else if (str[i] && str[i] != ' ')
			handle_others(str, &i);
	}
	return (0);
}
