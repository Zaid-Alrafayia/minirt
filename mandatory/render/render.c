/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 00:19:49 by jalghamd          #+#    #+#             */
/*   Updated: 2026/10/08 01:47:48 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

//delete this func after finishing the trace_ray (using it only for testing)
static t_color	test_color(t_ray ray)
{
	t_color	color;

	color.r = (ray.dir.x + 1.0) * 0.5;
	color.g = (ray.dir.y + 1.0) * 0.5;
	color.b = (ray.dir.z + 1.0) * 0.5;
	return (color);
}

//after finishing trace_ray call it here instead -> pack_color(tarce_ray(ray))
void	render_scene(t_app *app)
{
	int		x;
	int		y;
	t_ray	ray;
	int		color;

	camera_basis(&app->scene.cam);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = camera_ray(&app->scene.cam, (double)x, (double)y);
			color = pack_color(test_color(ray));
			put_pixel(&app->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(app->mlx, app->win, app->img.img_ptr, 0, 0);
}
