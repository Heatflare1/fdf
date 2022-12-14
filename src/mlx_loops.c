/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:32:36 by jmeruma           #+#    #+#             */
/*   Updated: 2023/01/10 15:02:14 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	reset_grid(t_map *map, t_map *oldmap)
{
	if (map->scale != oldmap->scale || ft_memcmp(&(map->cam),
			&(oldmap->cam), sizeof(t_camera)) != 0)
	{	
		ft_bzero(map->img->pixels, WIDTH * HEIGHT * sizeof(uint32_t));
		matrix(map);
		if ((cos(map->cam.rotate_y) > -0.71 && cos(map->cam.rotate_y) <= 1))
		{
			if ((sin(map->cam.rotate_y) > -0.71 && sin(map->cam.rotate_y) <= 1))
				draw_grid(map);
			else
				draw_reverse_grid(map);
		}
		else
			draw_reverse_grid(map);
	}
}

void	camera_loop(t_map *map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_UP))
		map->cam.y_offset -= 20;
	if (mlx_is_key_down(map->mlx, MLX_KEY_DOWN))
		map->cam.y_offset += 20;
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
		map->cam.x_offset -= 20;
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
		map->cam.x_offset += 20;
	if (mlx_is_key_down(map->mlx, MLX_KEY_1))
		map->cam.projection = 0;
	if (mlx_is_key_down(map->mlx, MLX_KEY_2))
		map->cam.projection = 1;
}

void	grid_loop(t_map	*map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_KP_ADD))
		map->scale++;
	if (mlx_is_key_down(map->mlx, MLX_KEY_KP_SUBTRACT))
		map->scale--;
	if (mlx_is_key_down(map->mlx, MLX_KEY_EQUAL))
		map->cam.height_offset--;
	if (mlx_is_key_down(map->mlx, MLX_KEY_MINUS))
		map->cam.height_offset++;
	if (mlx_is_key_down(map->mlx, MLX_KEY_Q))
		map->cam.rotate_y += 0.05;
	if (mlx_is_key_down(map->mlx, MLX_KEY_E))
		map->cam.rotate_y -= 0.05;
}

void	map_key_hook(void *param)
{
	t_map	*map;
	t_map	oldmap;

	map = param;
	oldmap = *((t_map *)param);
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map->mlx);
	camera_loop(map);
	grid_loop(map);
	reset_grid(map, &oldmap);
}
