/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:27:55 by pfrances          #+#    #+#             */
/*   Updated: 2022/06/07 10:58:44 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
/*		MAIN		*/
#include <stdio.h>
#include <fcntl.h>

#define FILE_NAME1 "file1.txt"
#define FILE_NAME2 "file2.txt"
#define FILE_NAME3 "file3.txt"
#define FILE_NAME4 "file4.txt"

int	main(void)
{
	char	*buff;
	int		fd;
	int		i = 0;

	printf("----------- Mandatory ----------------\n");
	fd = open(FILE_NAME1, O_RDONLY);
	while (1) {
		buff = get_next_line(fd);
		printf("i : %d str : %s", i, buff);
		if (!buff)
			break ;
		free(buff);
		i++;
	}
	printf("\n");
	close(fd);


	printf("\n----------- Bonus ----------------\n");
	int	fd_set[4];
	int	j;

	fd_set[0] = open(FILE_NAME1, O_RDONLY);
	fd_set[1] = open(FILE_NAME2, O_RDONLY);
	fd_set[2] = open(FILE_NAME3, O_RDONLY);
	fd_set[3] = open(FILE_NAME4, O_RDONLY);

	i = 0;
	j = 0;
	while (j < 50)
	{
		if (i == 4)
			i = 0;
		buff = get_next_line(fd_set[i]);
		printf("i : %d str : %s", i, buff);
		free(buff);
		i++;
		j++;
	}
	close(fd_set[0]);
	close(fd_set[1]);
	close(fd_set[2]);
	close(fd_set[3]);
	return (0);
}