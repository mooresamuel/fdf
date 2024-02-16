/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:50:37 by samoore           #+#    #+#             */
/*   Updated: 2024/02/16 17:26:02 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_box *box, double theta)
{
	double	y;
	double	z;
	double angle = theta * box->pi_div_180;

	for (int i = 0; i < (box->cols * box->rows); i++)
	{
		y = box->points[i].y;
		z = box->points[i].z;
		box->points[i].y = y * cos(angle) - sin(angle) * z;
		box->points[i].z = y * sin(angle) + z * cos(angle);
	}
}

void	rotate_y(t_box *box, double angle)
{
	double theta = angle * box->pi_div_180;
    double sinTheta = sin(theta);
    double cosTheta = cos(theta);

   	for (int n = 0; n < (box->cols * box->rows); n++) 
	{
        double x = box->points[n].x;
		double z = box->points[n].z;
		box->points[n].x = cosTheta * x + sinTheta * z;
		box->points[n].y = box->points[n].y;
		box->points[n].z = -sinTheta * x + cosTheta * z;
    }
}

void rotate_z(t_box *box, double angle)
{
	double theta = angle * box->pi_div_180;
    double sinTheta = sin(theta);
    double cosTheta = cos(theta);

    for (int n = 0; n < (box->cols * box->rows); n++) 
	{
        double x = box->points[n].x;
		double y = box->points[n].y;
		double tmpx, tmpy;
        tmpx = x * cosTheta - y * sinTheta;
        tmpy = y * cosTheta + x * sinTheta;
		box->points[n].x = tmpx;
		box->points[n].y = tmpy;
		box->points[n].z = box->points[n].z;
		box->points[n].x = box->points[n].x;
		box->points[n].y = box->points[n].y;
		box->points[n].z = box->points[n].z;
	 }
}
