/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 21:57:49 by cmichez           #+#    #+#             */
/*   Updated: 2022/12/26 19:37:54 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

char	*full_clear(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
		buf[i++] = 0;
	return (NULL);
}

char	*read_new_char(char *buffer, char *line)
{
	char	*res;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!line)
	{
		res = malloc((i + 2));
		ft_strncpy(res, buffer, i + 1);
		reset_buffer(buffer);
		return (res);
	}
	res = malloc(sizeof(char) * (i + ft_strlen(line) + 2));
	ft_strcpy(res, line);
	ft_strncat(res, buffer, i + 1);
	reset_buffer(buffer);
	free(line);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	tmp[BUFFER_SIZE + 1];
	char		*line;
	int			valeur_read;
	int			i;

	if (BUFFER_SIZE < 0 || read(fd, 0, 0) == -1)
		return (full_clear(tmp));
	line = NULL;
	if (check_buffer(&line, tmp))
		return (line);
	tmp[BUFFER_SIZE] = '\0';
	valeur_read = read(fd, tmp, BUFFER_SIZE);
	while (valeur_read >= 1)
	{
		i = 0;
		line = read_new_char(tmp, line);
		while (line[i])
		{
			if (line[i] == '\n')
				return (line);
			i++;
		}
		valeur_read = read(fd, tmp, BUFFER_SIZE);
	}
	return (line);
}

void	reset_buffer(char *buffer)
{
	int	i;

	while (buffer[0] && buffer[0] != '\n')
	{
		i = 0;
		while (buffer[i])
		{
			buffer[i] = buffer[i + 1];
			i++;
		}
	}
	i = 0;
	while (buffer[i])
	{
		buffer[i] = buffer[i + 1];
		i++;
	}
}

int	check_buffer(char **line, char *tmp)
{
	int		i;
	char	j;

	i = 0;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (i == 0 && tmp[i] != '\n')
		return (0);
	*line = malloc(sizeof(char) * (i + 2));
	ft_strncpy(*line, tmp, i + 1);
	j = tmp[i];
	reset_buffer(tmp);
	if (j == '\0')
		return (0);
	return (1);
}
