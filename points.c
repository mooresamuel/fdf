/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:31:01 by samoore           #+#    #+#             */
/*   Updated: 2024/02/16 16:17:00 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	make_x_y(t_box *box)
{
	int	i;
	int	j;

	i = 0;
	while (i < box->rows)
	{
		j = 0;
		while (j < box->cols)
		{
			box->origin[i * box->cols + j].x = (double)(j - box->cols / 2);
			box->map[i * box->cols + j].x =  (double)(j - box->cols / 2);
			box->points[i * box->cols + j].x =  (double)(j - box->cols / 2);
			box->origin[i * box->cols + j].y = (double)(i - box->rows / 2);
			box->map[i * box->cols + j].y = (double)(i - box->rows / 2);
			box->points[i * box->cols + j].y = (double)(i - box->rows / 2);
			j++;
		}
		i++;
	}
}

void	make_points(t_box *box, char **nums, int i)
{
	int	j;
	int	tmp;
	int	colour;

	j = 0;
	if (!nums)
		return ;
	while (nums[j])
	{
		tmp = ft_atoi(nums[j]);
		box->origin[i * box->cols + j].z = (double)tmp;
		box->map[i * box->cols + j].z = (double)tmp;
		colour = (int)box->map[i * box->cols + j].z + 85 + rand() % 150;
		box->points[i * box->cols + j].colour = encode_rgb(colour , 75, 75);
		free (nums[j++]);
	}
	free (nums);
	nums = NULL;
}
