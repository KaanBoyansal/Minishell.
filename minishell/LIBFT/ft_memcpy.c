/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyansa <mboyansa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:00:19 by mboyansa          #+#    #+#             */
/*   Updated: 2023/10/30 13:30:18 by mboyansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*source;
	char	*dest;

	source = (char *)src;
	dest = (char *)dst;
	i = 0;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		dest[i] = source[i];
		i++;
	}
	return (dest);
}
