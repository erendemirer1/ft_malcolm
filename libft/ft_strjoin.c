/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edemirer <edemirer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:01:13 by edemirer          #+#    #+#             */
/*   Updated: 2023/07/06 16:23:34 by edemirer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	tmp = (char *)malloc((len + 1) * sizeof(char));
	if (!tmp || (!s1 && !s2))
		return (NULL);
	while (*(s1 + i))
	{
		*(tmp + i) = *(s1 + i);
		i++;
	}
	while (*(s2 + j))
		*(tmp + i++) = *(s2 + j++);
	*(tmp + i) = '\0';
	return (tmp);
}
