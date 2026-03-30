/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edemirer <edemirer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:15:00 by edemirer          #+#    #+#             */
/*   Updated: 2023/07/08 19:42:20 by edemirer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	const char	*buffer1;
	char		*buffer2;

	i = 0;
	buffer1 = (char *)src;
	buffer2 = (char *)dst;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		buffer2[i] = buffer1[i];
		i++;
	}
	return (dst);
}
