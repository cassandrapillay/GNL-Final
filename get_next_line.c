/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpillay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 15:29:37 by cpillay           #+#    #+#             */
/*   Updated: 2018/07/06 10:24:09 by cpillay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_nextline(char **str, char **line, int fd, int buffer)
{
	int		i;
	char	*temp;
	char	*new;

	i = 0;
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		i++;
	if ((*str)[i] == '\n')
	{
		temp = *str;
		*line = ft_strsub(temp, 0, i);
		temp = ft_strchr(temp, '\n') + 1;
		new = ft_strdup(temp);
		free(*str);
		*str = new;
	}
	else if ((*str)[i] == '\0')
	{
		if (buffer == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(*str);
		ft_strdel(str);
		i++;
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	int			bytes;
	static char *str = NULL;
	char		*temp;
	char		buffer[BUFF_SIZE + 1];

	if (fd < 0 || line == NULL)
		return (-1);
	*line = "";
	while ((bytes = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[bytes] = '\0';
		if (str == NULL)
			str = ft_strnew(1);
		temp = ft_strjoin(str, buffer);
		free(str);
		str = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (bytes < 0)
		return (-1);
	else if ((str == NULL || str[0] == '\0') && bytes == 0)
		return (0);
	return (ft_nextline(&str, line, fd, bytes));
}
