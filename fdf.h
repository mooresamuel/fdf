/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:33:09 by samoore           #+#    #+#             */
/*   Updated: 2024/02/16 17:37:31 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

# define WIDE	1920
# define HIGH	780
# define LEFT	65361
# define RIGHT	65363	
# define UP		65362
# define DOWN	65364
# define PLUS	0xffab
# define MINUS  0xffad
# define H		0x68

typedef unsigned char	byte;

typedef struct s_rotation_matrix
{
	double	matrix[3][3];
}	t_rotation_matrix;

typedef struct s_line
{
	int	dx;
	int	dy;
	int	err;
	int	e2;
	int	sx;
	int	sy;
}	t_line;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	int	colour;
}	t_point;

typedef struct s_edge
{
	t_point *start;
	t_point *end;
}	t_edge;

typedef struct s_box
{
	void	*mlx;
	void	*win;
	char	**nums;
	int		bpp_offset;
	int		center_x;
	int		center_y;
	int		colour;
	int		x_angle;
	int		y_angle;
	int		z_angle;
	int		x_momentum;
	int		y_momentum;
	int		z_momentum;
	int		cols;
	int		rows;
	int		hide;
	int		num_edges;
	double	pi_div_180;
	double	elevation;
	int		resize;
	double	radius;
	void	*img;
	char	*img_ptr;
	int		bpp;
	int		endian;
	int		line_len;
	t_point	*origin;
	t_point	*map;
	t_point	*points;
	t_edge	*edges;
}	t_box;
/*
void	draw_cube(t_box *box);
void	draw_line(t_box *dat, t_point *start, t_point *end);
int		encode_rgb(byte red, byte green, byte blue);
void	init_cube(t_box *box);
int		my_pixel_put(t_box *box, int x, int y, int colour);
void	read_map(t_box *box, char *file);

void	rotate_cube(t_point *cube, int angle);
void	rotate_x(t_box *box, double theta);
void	rotate_y(t_box *box, double theta);
void	rotate_z(t_box *box, double theta);

void	draw_map(t_box *box);
int		end_mouse_1(int button, t_box *box);
void	end_program(t_box *box);
void	read_map(t_box *box, char *file);
char	**ft_split_space(char *str);
int		kill(int input);
t_edge	*make_map(t_box *box);
void	make_points(t_box *box, char **nums, int i);
void	make_x_y(t_box *box);
int		mouse(int action);
int		mouse_hook(int button, t_box *box);
void	read_map(t_box *box, char *file);
double	zoom(int trigger);
void	x_pressed(t_box *box);

t_point translate_mouse(t_point mouseMovement, t_rotation_matrix rotate);
*/
void    draw_line(t_box *box, t_point *start, t_point *end);
void    draw_map(t_box *box);
int     encode_rgb(byte red, byte green, byte blue);
int     end_mouse_1(int button, t_box *box);
void    end_program(t_box *box);

char    **ft_split_space(char *str);
void    make_points(t_box *box, char **nums, int i);
void    make_x_y(t_box *box);
void    read_map(t_box *box, char *file);
t_edge  *make_map(t_box *box);
int     mouse(int action);
int     mouse_hook(int button, t_box *box);

void    rotate_x(t_box *box, double theta);
void    rotate_y(t_box *box, double theta);
void    rotate_z(t_box *box, double theta);
void    x_pressed(t_box *box);
double  zoom(int trigger);

#endif
