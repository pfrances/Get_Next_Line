/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:21:04 by pfrances          #+#    #+#             */
/*   Updated: 2022/06/06 15:33:35 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}		t_bool;

typedef enum e_success
{
	ERROR,
	SUCCESS,
	CONTINUE
}		t_success;

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*ft_strndup(const char *s1, size_t n);
void	ft_bzero(void *b, size_t len);

#endif