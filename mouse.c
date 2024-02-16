/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:40:13 by samoore           #+#    #+#             */
/*   Updated: 2024/02/15 18:04:42 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse(int action)
{
	static int	state = 0;

	if (action == 1)
		state = 1;
	if (action == 2)
		state = 2;
	if (action == 0)
		return (state);
	if (action == -1)
		state = 0;
	return (0);
}

int	end_mouse_1(int button, t_box *box)
{
	if (button == 1)
	mouse(2);
}

int	start_mouse_1(t_box *box)
{
	mouse(1);
}

int	mouse_hook(int button, t_box *box)
{
	if (button == 1)
		start_mouse_1(box);
	if (button == 4)
		zoom(1);
	if (button == 5)
		zoom(2);
}

double	zoom(int trigger)
{
	static double value = 100;
	static int resize = 0;

	if (trigger == 1)
	{
		resize = 1;
		value += 10;
	}
	if (trigger == 2 && value > 10)
	{
		resize = 1;
		value -= 10;
	}
	if (trigger == 0)
		return (resize);
	if (trigger == -1)
	{
		resize = 0;
		return (value);
	}
	return (0);
}
