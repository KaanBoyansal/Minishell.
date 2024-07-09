/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyansa <mboyansa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:33:52 by mboyansa          #+#    #+#             */
/*   Updated: 2023/10/30 13:30:18 by mboyansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*result;	

	c = (unsigned char)c;
	i = ft_strlen(str);
	result = (char *)str;
	if (c == 0)
		return (&result[i]);
	while (i >= 0)
	{
		if (result[i] == c)
			return (&result[i]);
		if (i > 0)
			i--;
		else
			break ;
	}
	return (0);
}
