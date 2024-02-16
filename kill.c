/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:43:44 by samoore           #+#    #+#             */
/*   Updated: 2024/02/16 17:30:32 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	end_program(t_box *box)
{
		mlx_destroy_image(box->mlx, box->img_ptr);
		mlx_destroy_window(box->mlx, box->win);
		mlx_destroy_display(box->mlx);
		free (box->mlx);
		free (box->points);
		free (box->map);
		free (box->edges);
		free (box->origin);
		exit (1);
}

int	kill(int input)
{
	static int	kill = 0;

	if (input == 1)
		kill = 1;
	return (kill);
}

void	x_pressed(t_box *box)
{
	kill (1);
}
