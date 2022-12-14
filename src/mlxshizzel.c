/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxshizzel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:55:38 by jmeruma           #+#    #+#             */
/*   Updated: 2022/12/14 11:27:27 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

int	render_background(mlx_t *mlx)
{
	int			x;
	int			y;
	mlx_image_t	*img;

	x = 0;
	y = 0;
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			mlx_put_pixel(img, x, y, 0x0000000FF);
			x++;
		}
		x = 0;
		y++;
	}
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		return (1);
	return (0);
}

void	my_key_hook(void *param)
{
	t_map	*map;

	map = param;
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map->mlx);
	if (mlx_is_key_down(map->mlx, MLX_KEY_UP))
	{
		ft_bzero(map->img->pixels, WIDTH * HEIGHT * BPP);
		map->cam->y_offset -= 10;
		matrix(map);
		draw_grid(map);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_DOWN))
	{
		ft_bzero(map->img->pixels, WIDTH * HEIGHT * BPP);
		map->cam->y_offset += 10;
		matrix(map);
		draw_grid(map);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		ft_bzero(map->img->pixels, WIDTH * HEIGHT * BPP);
		map->cam->x_offset -= 10;
		matrix(map);
		draw_grid(map);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		ft_bzero(map->img->pixels, WIDTH * HEIGHT * BPP);
		map->cam->x_offset += 10;
		matrix(map);
		draw_grid(map);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_KP_ADD))
	{
		ft_bzero(map->img->pixels, WIDTH * HEIGHT * BPP);
		map->scale++;
		matrix(map);
		draw_grid(map);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_KP_SUBTRACT))
	{
		ft_bzero(map->img->pixels, WIDTH * HEIGHT * BPP);
		map->scale--;
		matrix(map);
		draw_grid(map);
	}
}

int32_t	mlx(t_map *map)
{
	map->mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!map->mlx)
		cleanerror(3, map);
	map->img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	if (!map->img)
		cleanerror(3, map);
	map->scale = STD_SCALE;
	if (render_background(map->mlx) != 0)
		cleanerror(4, map);
	matrix(map);
	draw_grid(map);
	if (mlx_image_to_window(map->mlx, map->img, 0, 0) == -1)
		cleanerror(4, map);
	mlx_loop_hook(map->mlx, &my_key_hook, map);
	mlx_loop(map->mlx);
	mlx_terminate(map->mlx);
	return (0);
}
