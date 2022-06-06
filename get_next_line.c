/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:26:15 by pfrances          #+#    #+#             */
/*   Updated: 2022/06/06 16:31:53 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_and_return(char *result, char **save, char *buff, int flag)
{
	free(buff);
	if (flag == SUCCESS)
		return (result);
	free(result);
	free(*save);
	*save = NULL;
	return (NULL);
}

int	initialisation(char **result, char **save, char **buff)
{
	if (*save)
	{
		*result = *save;
		*save = NULL;
	}
	else
	{
		*result = ft_strndup("", 1);
		if (!*result)
			return (ERROR);
	}
	*buff = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!*buff)
		return (ERROR);
	return (SUCCESS);
}

int	search_line_break(char **result, char **save, size_t *i)
{
	while ((*result)[*i] != '\0')
	{
		if ((*result)[*i] == '\n')
		{
			*save = ft_strndup(*result + *i + 1, ft_strlen(*result + *i));
			if (!*save)
				return (ERROR);
			(*result)[*i + 1] = '\0';
			return (SUCCESS);
		}
		(*i)++;
	}
	return (CONTINUE);
}

char	*get_line_and_save(char **result, char **save, char **buff, int fd)
{
	int		line_break_flag;
	size_t	i;
	ssize_t	nb_read;

	i = 0;
	while (1)
	{
		ft_bzero(*buff, ((size_t)BUFFER_SIZE + 1));
		nb_read = read(fd, *buff, BUFFER_SIZE);
		if (nb_read <= 0 && (!(*result)[0] || !(*result)[i]))
			return (free_and_return(*result, save, *buff, (*result)[0]));
		*result = ft_strjoin(*result, *buff);
		if (!*result)
			return (free_and_return(*result, save, *buff, ERROR));
		line_break_flag = search_line_break(result, save, &i);
		if (line_break_flag == SUCCESS || line_break_flag == ERROR)
			return (free_and_return(*result, save, *buff, line_break_flag));
	}
}

char	*get_next_line(int fd)
{
	static char	*save = NULL;
	char		*buff;
	char		*result;

	if (fd < 0 || fd > _SC_OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (initialisation(&result, &save, &buff) == ERROR)
		return (NULL);
	return (get_line_and_save(&result, &save, &buff, fd));
}
