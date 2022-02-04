/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haniakhater <haniakhater@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:12:35 by haniakhater       #+#    #+#             */
/*   Updated: 2022/02/04 18:03:12 by haniakhater      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

int	ft_find_newline(char *buff)
{
	int	i;

	i = 0;
	if (buff == NULL)
		return (-1);
	while (buff[i] != '\0')
	{
		if (buff[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_split_remaining(char **line, char **remaining, char **buff, int newline)
{
	*line = ft_substr(*remaining, 0, (newline + 1));
	if (!(*line))
		return (ft_free(line, remaining, NULL));
	*buff = ft_substr(*remaining, (newline + 1), BUFFER_SIZE);
	if (!(*buff))
		return (ft_free(line, remaining, NULL));
	free (*remaining);
	*remaining = ft_substr(*buff, 0, BUFFER_SIZE);
	if (!(*remaining))
		return (ft_free(line, remaining, buff));
	free (*buff);
	return (*line);
}

char	*ft_split_buffer(char **line, char **remaining, char **buff, int newline)
{
	*remaining = ft_substr(*buff, 0, (newline + 1));
	if (!(*remaining))
		return (ft_free(remaining, buff, line));
	*line = ft_linejoin(*line, *remaining);
	if (!(*line))
		return (ft_free(buff, NULL, NULL));
	free (*remaining);
	*remaining = ft_substr(*buff, (newline + 1), BUFFER_SIZE);
	if (!(*remaining))
		return (ft_free(remaining, buff, line));
	free (*buff);
	return (*line);
}

char	*ft_read(int fd, char **remaining, char **buff, char **line)
{
	int	b;
	int	newline;

	while (1)
	{
		b = read(fd, *buff, BUFFER_SIZE);
		if (b < 0)
			return (ft_free(remaining, buff, line));
		if (b == 0)
		{
			ft_free(buff, NULL, NULL);
			if (ft_strlen(*line) != 0)
				return (*line);
			return (ft_free(line, NULL, NULL));
		}
		(*buff)[b] = '\0';
		newline = ft_find_newline(*buff);
		if (newline != -1)
			return (ft_split_buffer(line, remaining, buff, newline));
		*line = ft_linejoin(*line, *buff);
		if (!(*line))
			return (ft_free(buff, NULL, NULL));
	}
}

char	*get_next_line(int fd)
{
	static char	*remaining;
	char		*buff;
	char		*line;
	int			newline;

	newline = ft_find_newline(remaining);
	if (newline != -1)
		return (ft_split_remaining(&line, &remaining, &buff, newline));
	buff = (char *)malloc((sizeof(char) * BUFFER_SIZE) + 1);
	line = (char *)malloc(sizeof(char) * 1);
	if (!buff || !line || fd < 0)
		return (ft_free(&remaining, &buff, &line));
	line[0] = '\0';
	line = ft_linejoin(line, remaining);
	if (!line)
		return (ft_free(&buff, NULL, NULL));
	ft_free(&remaining, NULL, NULL);
	return (ft_read(fd, &remaining, &buff, &line));
}
