/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:56:05 by samoore           #+#    #+#             */
/*   Updated: 2024/02/16 16:41:17 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	join(t_point *start, t_point *end, t_edge *edge)
{
	edge->start = start;
	edge->end = end;
}

void	draw_map(t_box *box)
{
	int	i;

	i = 0;
	while (i < box->num_edges)
	{
		draw_line(box, box->edges[i].start, box->edges[i].end);
		i++;
	}
}

t_edge	*make_map(t_box *box)
{
	t_edge	*res;
	int		i;
	int		j;
	int		pos;
	int		edge;

	edge = 0;
	box->num_edges = box->rows * box->cols + (box->rows - 1) * (box->cols);
	res = malloc(sizeof(t_edge) * (box->num_edges + 1));
	if (!res)
		exit (3);
	i = 0;
	while (i < box->rows)
	{
		j = 0;
		while (j <= box->cols)
		{
			pos = i * box->cols + j;
			if (j < box->cols - 1)
				join(&box->points[pos], &box->points[pos + 1], &res[edge++]);
			else
				join(&box->points[pos - 1], &box->points[pos - box->cols + 1], &res[edge++]);
			if (i < box->rows - 1 && j < box->cols - 1)
				join(&box->points[pos], &box->points[pos + box->cols], &res[edge++]);
			j++;
		}
		i++;
	}
	return (res);
}
