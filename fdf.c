/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:27:43 by samoore           #+#    #+#             */
/*   Updated: 2024/02/16 17:36:42 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	encode_rgb(byte red, byte green, byte blue)
{
	return (red << 16 | green << 8 | blue);
}

void	print_map(t_box *box)
{
	int	i;
	int	j;

	i = 0;
	while (i < box->rows)
	{
		j = 0;
		while (j <  box->cols)
		{
			printf("x %lf, y %lf, z %lf\n", box->origin[i * box->cols + j].x, box->origin[i * box->cols + j].y, box->origin[i * box->cols + j].z);
			j++;
		}
		i++;
	}
}
void	add_momentum(t_box *box, t_point start, t_point end)
{
	t_rotation_matrix	r_matrix;
	t_point				mouse_movement;
	t_point				translated_movement;

	mouse_movement.x = end.x - start.x;
	mouse_movement.y = (end.y - start.y);
//	get_rotation_matrix(&r_matrix, box->x_angle, box->y_angle, box->z_angle);
//	mouse_movement = translate_mouse(mouse_movement, r_matrix);
//	if (box->x_angle < 180)
//		box->x_momentum += end.x - start.x;
//	else
//	if ((box->y_angle > 180 ^ box->x_angle > 180) || (box->x_angle < 180 ^ box->y_angle < 180))
//		box->x_momentum -= mouse_movement.x;
//	else
		box->x_momentum += (int)end.x - (int)start.x;
//	if ((box->y_angle > 180 ^ box->x_angle > 180) || (box->x_angle < 180 ^ box->y_angle < 180))
//		box->y_momentum -= mouse_movement.y;
//	else
		box->y_momentum += (int)mouse_movement.y;
//	if ()
//		box->y_momentum -= mouse_movement.y;
//	else
//		box->y_momentum += mouse_movement.y;
}

int	handle_input(int keysym, t_box *box)
{
	/* keysym is an abstraction of the key pressed in order to account for different hardware.
	On a sysytem with a qwerty or azerty keyboard, the letter a would have a different value
	(key code) but the keysym will be the same.
	*/
	if (keysym == XK_Escape)
	{
		kill (1);
	}
	if (keysym == RIGHT)
		box->center_x += 10;
	if (keysym == LEFT)
		box->center_x -= 10;
	if (keysym == UP)
		box->center_y -= 7;
	if (keysym == DOWN)
		box->center_y += 7;
	if (keysym == PLUS)
		box->elevation += 1;
	if (keysym == MINUS && box->elevation > 1)
		box->elevation -= 1;
	if (keysym == H)
		box->hide = !box->hide;
}

void	check_mouse(t_box *box)
{
	static t_point	start;
	static t_point	end;

	if (mouse(0) == 1)
	{
		mlx_mouse_get_pos(box->mlx, box->win, &start.x, &start.y);
		mouse(-1);
	}
	else if (mouse(0) == 2)
	{
		mlx_mouse_get_pos(box->mlx, box->win, &end.x, &end.y);
		mouse(-1);
		add_momentum(box, start, end);
		start.x = 0;
		start.y = 0;
		end.x = 0;
		end.y = 0;
	}
}

void make_sphere(t_box *box, double radius) 
{
	double	theta;
	double	phi;
    int		i;
	int		j;
	int		pos;
	int		zoom;

	i = 0;
    while (i < box->rows)
	{
		j = 0;
        while (j < box->cols) 
		{
			pos = i * box->cols + j;
			theta = 2.0 * M_PI * j / (box->cols - 1);    // Longitude (azimuthal angle)
            phi = M_PI * i / (box->rows - 1);       // Latitude (polar angle)
            box->map[pos].x = (radius + box->origin[pos].z * box->elevation)  * sin(phi) * cos(theta);
            box->map[pos].y = (radius + box->origin[pos].z * box->elevation) * sin(phi) * sin(theta);
            box->map[pos].z = (radius + box->origin[pos].z * box->elevation) * cos(phi);
            j++;
        }
		i++;
    }

	for (int i = 0; i < box->rows * box->cols; i++)
	{
		box->points[i].x = box->map[i].x;
		box->points[i].y = box->map[i].y;
		box->points[i].z = box->map[i].z;
	}

}

void	check_angles(t_box *box)
{
	if (box->x_angle < 0)
		box->x_angle = 360 - box->x_angle;
	else if (box->x_angle > 360)
		box->x_angle = box->x_angle - 360;
	if (box->y_angle < 0)
		box->y_angle = 360 - box->y_angle;
	else if (box->y_angle > 360)
		box->y_angle = box->y_angle - 360;
}

void	check_momentum(t_box *box)
{
	if (box->y_momentum != 0)
	{
		box->x_angle += box->y_momentum / 80;
		box->y_momentum -= box->y_momentum / 80;
		if (box->y_momentum > 0)
		{
			box->x_angle--;
			box->y_momentum--;
		}
		else
		{
			box->x_angle++;
			box->y_momentum++;
		}
	}
	if (box->x_momentum != 0)
	{
		box->y_angle += box->x_momentum / 80;
		box->x_momentum -= box->x_momentum / 80;
		if (box->x_momentum > 0)
		{
			box->y_angle--;
			box->x_momentum--;
		}
		else
		{
			box->y_angle++;
			box->x_momentum++;
		}
	}	
}
void	main_loop(t_box *box)
{
	static int	r;
	if (kill(0))
		end_program (box);
	check_mouse(box);
	check_momentum(box);
//	if (zoom(0))
//	{
//		box->radius = zoom(-1);
//		box->resize = 1;
//	}
	mlx_destroy_image(box->mlx, box->img);
	box->img = mlx_new_image(box->mlx, WIDE, HIGH);
//	if (box->resize)
//	{
//		make_sphere(box, box->radius);
//		box->resize = 0;
//	}
//	box->x_momentum++;
//	box->x_angle++;
//	box->y_angle++;
//	rotate_z(box, box->z_angle);
	rotate_x(box, box->x_momentum);
	rotate_y(box, box->y_momentum);
	rotate_z(box, 0);
	draw_map(box);
	mlx_put_image_to_window(box->mlx, box->win, box->img, 0, 0);
	printf("x %d y %d\n", box->x_angle, box->y_angle);
//	usleep(1);
//	check_angles(box);
}

int	main(void)
{
	t_box	box;

	box.x_angle = 0;
	box.y_angle = 0;
	box.z_angle = 0;
	box.x_momentum = 0;
	box.y_momentum = 0;
	box.pi_div_180 = M_PI / 180;
	box.radius = 300;
	box.center_x = WIDE / 2;
	box.center_y = HIGH / 2;
	box.elevation = 1;
	read_map(&box, "mars.fdf");
	make_x_y(&box);
	box.edges = make_map(&box);
	make_sphere(&box, box.radius);
	box.mlx = mlx_init();
	if (!box.mlx)
		exit (1);
	box.win = mlx_new_window(box.mlx, WIDE, HIGH, "Fdf");
	if (!box.win)
	{
		mlx_destroy_display(box.mlx);
		free (box.mlx);
		exit (2);
	}
	box.img = mlx_new_image(box.mlx, WIDE, HIGH);
	box.img_ptr = mlx_get_data_addr(box.img, &box.bpp, &box.line_len, &box.endian);
	box.bpp_offset = box.bpp / 8;
	mlx_key_hook(box.win, handle_input, &box);
	mlx_hook(box.win, 17, 1L<<17, x_pressed, &box);
	mlx_hook(box.win, 5, 1L<<3, end_mouse_1, &box);
	mlx_mouse_hook(box.win, mouse_hook, &box);
	mlx_loop_hook(box.mlx, main_loop, &box);
	mlx_loop(box.mlx);
	printf("fin\n");
}
