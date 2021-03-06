/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:38:41 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/05 15:42:57 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	render(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	if (data->win_ptr == NULL)
		return (1);
	render_background(data->img, BACKGROUND);
	while (y < data->map->y_max)
	{
		x = 0;
		while (x < data->map->x_max)
		{
			if ((x + 1) < data->map->x_max)
				draw_line(data, &data->map->vec[y][x], \
						&data->map->vec[y][x + 1]);
			if ((y + 1) < data->map->y_max)
				draw_line(data, &data->map->vec[y][x], \
						&data->map->vec[y + 1][x]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
			data->img->mlx_img, 0, 0);
	return (0);
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	*pixel;
	int	size;

	pixel = (int *)img->addr;
	size = WINDOW_HEIGHT * WINDOW_WIDTH;
	i = 0;
	while (i < size)
	{
		pixel[i] = color;
		i++;
	}
}
