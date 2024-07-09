/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyansa <mboyansa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:54:23 by mboyansa          #+#    #+#             */
/*   Updated: 2023/10/30 12:54:24 by mboyansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	link_lstadd_back(t_ink_list **lst, t_ink_list *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	link_lstlast(*lst)->next = new;
}

void	link_lstclear(t_ink_list **lst)
{
	t_ink_list	*tmp;

	if (!lst)
	{
		return ;
	}
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		link_lstdelone(*lst);
		*lst = tmp;
	}
}

void	link_lstdelone(t_ink_list *lst)
{
	if (!lst)
		return ;
	free(lst->content);
	free(lst);
}

t_ink_list	*link_lstlast(t_ink_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_ink_list	*link_lstnew(char *content, char flag)
{
	t_ink_list	*str;

	str = malloc(sizeof(t_ink_list));
	if (!str)
		return (0);
	str->content = content;
	str->flag = flag;
	str->next = NULL;
	return (str);
}
