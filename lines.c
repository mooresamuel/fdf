/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:36:57 by samoore           #+#    #+#             */
/*   Updated: 2024/02/16 16:49:00 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	prep_line(t_line *line, t_point *start, t_point *end)
{
	line->dx = abs ((int)end->x - (int)start->x);
	line->dy = -abs((int)end->y - (int)start->y);
	if (start->x < end->x)
		line->sx = 1;
	else
		line->sx = -1;
	if (start->y < end->y)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx + line->dy;
}

int	my_pixel_put(t_box *box, int x, int y, int colour)
{
	int	offset;

	x += box->center_x;
	y += box->center_y;
	offset = (box->line_len * y) + (x * box->bpp_offset);
	if (x >= 0 && x < WIDE && y >= 0 && y < HIGH)
		*((unsigned int *)(offset + box->img_ptr)) = colour;
}

void	draw_line(t_box *box, t_point *start, t_point *end)
{
	t_line	line;
	int		x;
	int		y;
	int		end_x;
	int		end_y;

//	if (box->hide && ((int)start->z < box->radius / 2 && (int)end->z < box->radius / 2))
//		return ;
	prep_line(&line, start, end);
	x = (int)start->x;
	y = (int)start->y;
	end_x = (int)end->x;
	end_y = (int)end->y;

	while (x != end_x || y != end_y)
	{
		my_pixel_put(box, x, y, start->colour);
		line.e2 = 2 * line.err;
		if (line.e2 >= line.dy)
		{
			line.err += line.dy;
			x += line.sx;
		}
		if (line.e2 <= line.dx)
		{
			line.err += line.dx;
			y += line.sy;
		}
	}
}
