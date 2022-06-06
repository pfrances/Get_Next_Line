/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:26:15 by pfrances          #+#    #+#             */
/*   Updated: 2022/06/06 16:54:12 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
		if (nb_read <= 0 && (!**result || !(*result)[i]))
			return (free_and_return(*result, save, *buff, **result != '\0'));
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
	static char	*save[10240] = {NULL};
	char		*buff;
	char		*result;

	if (fd < 0 || fd >= 10240 || BUFFER_SIZE <= 0)
		return (NULL);
	if (initialisation(&result, &save[fd], &buff) == ERROR)
		return (NULL);
	return (get_line_and_save(&result, &save[fd], &buff, fd));
}

/////////////////////////////////////////////////////////////////
// /*		MAIN		*/
// #include <stdio.h>
// #include <fcntl.h>

// #define FILE_NAME1 "file1.txt"
// #define FILE_NAME2 "file2.txt"
// #define FILE_NAME3 "file3.txt"
// #define FILE_NAME4 "file4.txt"

// int	main(void)
// {
// 	char	*buff;
// 	int		fd;
// 	int		i = 0;

// 	printf("----------- Mandatory ----------------\n");
// 	fd = open(FILE_NAME1, O_RDONLY);
// 	while (1) {
// 		buff = get_next_line(fd);
// 		printf("i : %d str : %s", i, buff);
// 		if (!buff)
// 			break ;
// 		free(buff);
// 		i++;
// 	}
// 	printf("\n");
// 	close(fd);

// 	printf("\n----------- Bonus ----------------\n");
// 	int	fd_set[4];
// 	int	j;

// 	fd_set[0] = open(FILE_NAME1, O_RDONLY);
// 	fd_set[1] = open(FILE_NAME2, O_RDONLY);
// 	fd_set[2] = open(FILE_NAME3, O_RDONLY);
// 	fd_set[3] = open(FILE_NAME4, O_RDONLY);

// 	i = 0;
// 	j = 0;
// 	while (j < 50)
// 	{
// 		if (i == 4)
// 			i = 0;
// 		buff = get_next_line(fd_set[i]);
// 		printf("i : %d str : %s", i, buff);
// 		free(buff);
// 		i++;
// 		j++;
// 	}
// 	close(fd_set[0]);
// 	close(fd_set[1]);
// 	close(fd_set[2]);
// 	close(fd_set[3]);
// 	return (0);
// }
