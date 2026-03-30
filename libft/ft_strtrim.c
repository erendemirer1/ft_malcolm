/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edemirer <edemirer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 23:28:23 by edemirer          #+#    #+#             */
/*   Updated: 2023/07/08 19:41:47 by edemirer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_search(int s1, const char *set)
{
	size_t	i;

	i = 0;
	while (*(set + i))
	{
		if (*(set + i) == s1)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tmp;
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	i = 0;
	end = ft_strlen(s1);
	while (ft_search(s1[start], set))
		start++;
	while (end > start && ft_search(s1[end - 1], set))
		end--;
	tmp = malloc(sizeof(char) * (end - start + 1));
	if (!tmp)
		return (NULL);
	while (start < end)
	{
		*(tmp + i) = *(s1 + start);
		i++;
		start++;
	}
	*(tmp + i) = '\0';
	return (tmp);
}
