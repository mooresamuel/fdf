/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:39:41 by samoore           #+#    #+#             */
/*   Updated: 2024/02/16 13:41:14 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	num_lines(char *file)
{
	char	c;
	int		fd;
	int		res;
	int		bytes;
	
	res = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		exit (1);
	}
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, &c, 1);
		if (c == '\n')
			res++;
	}
	close (fd);
	return (res - 1);
}

char	*re_alloc(char *str, int *size)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * *size * 2);
	while (i < *size)
	{
		res[i] = str[i];
		i++;
	}
	*size *= 2;
	free (str);
	return (res);
}

char	*gnl(int fd)
{
	char	*res;
	char	c;
	int		i;
	int		size;
	int		bytes;

	size = 128;
	bytes = 1;
	i = 0;
	res = malloc(sizeof(char) * size);
	while (bytes > 0)
	{
		bytes = read(fd, &c, 1);
		if (i == size - 1)
			res = re_alloc(res, &size);
		if (!c || c == '\n')
		{
			res[i] = 0;
			return (res);
		}
		res[i++] = c;
	}
	free (res);
	return (NULL);
}

void	read_map(t_box *box, char *file)
{
	char 	*str;
	char	**nums;
	int		fd;
	int		i;

	i = 0;
	box->cols = 0;
	box->rows = num_lines(file);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		exit (1);
	}
	while (i < box->rows)
	{
		str = gnl(fd);
		nums = ft_split_space(str);
		if (box->cols == 0)
		{
			while (nums[box->cols])
				box->cols++;
			box->origin = malloc(sizeof(t_point) * box->cols * box->rows);
			box->map = malloc(sizeof(t_point) * box->cols * box->rows);
			box->points = malloc(sizeof(t_point) * box->cols * box->rows);
		}
		make_points(box, nums, i);
		i++;
	}
	close(fd);	
}
