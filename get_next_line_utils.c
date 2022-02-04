/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haniakhater <haniakhater@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:12:37 by haniakhater       #+#    #+#             */
/*   Updated: 2022/02/04 18:03:14 by haniakhater      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	num;

	num = 0;
	while (*s != '\0')
	{
		num++;
		s++;
	}
	return (num);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < len && s[i + start] != '\0' && start < ft_strlen(s))
		i++;
	subs = (char *)malloc(sizeof(char) * (i + 1));
	if (!subs)
		return (NULL);
	while (j < i)
	{
		subs[j] = s[j + start];
		j++;
	}
	subs[j] = '\0';
	return (subs);
}

char	*ft_free(char **str1, char **str2, char **str3)
{
	if (str1)
	{
		free (*str1);
		*str1 = NULL;
	}
	if (str2)
	{
		free (*str2);
		*str2 = NULL;
	}
	if (str3)
	{
		free (*str3);
		*str3 = NULL;
	}
	return (NULL);
}

char	*ft_linejoin(char *old_line, char *add)
{
	int		i;
	int		j;
	size_t	len_1;
	size_t	len_2;
	char	*new_line;

	if (!add)
		return (old_line);
	i = 0;
	j = 0;
	len_1 = ft_strlen(old_line);
	len_2 = ft_strlen(add);
	new_line = (char *)malloc(sizeof(char) * (len_1 + len_2 + 1));
	if (!new_line)
		return (ft_free(&old_line, &add, NULL));
	while (old_line[j] != '\0')
		new_line[i++] = old_line[j++];
	while (*add != '\0')
		new_line[i++] = *(add++);
	new_line[i] = '\0';
	free (old_line);
	return (new_line);
}