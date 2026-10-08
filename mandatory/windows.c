/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:10:17 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/10/08 03:40:34 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	close_program(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (!app)
		exit(0);
	if (app->img.img_ptr)
		mlx_destroy_image(app->mlx, app->img.img_ptr);
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	if (app->mlx)
	{
		mlx_destroy_display(app->mlx);
		free(app->mlx);
	}
	free_scene(&app->scene);
	free(app);
	exit(0);
	return (0);
}

int	key_handler(int keycode, void *param)
{
	if (keycode == 65307)
		return (close_program(param));
	return (0);
}

void	init_window(t_app *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
	{
		free_scene(&app->scene);
		free(app);
		perror("Error: Failed to initialize MiniLibX.");
		exit(1);
	}
	app->win = mlx_new_window(app->mlx, WIDTH, HEIGHT, "miniRT");
	if (!app->win)
		return (close_program(app), 0);
	app->img.img_ptr = mlx_new_image(app->mlx, WIDTH, HEIGHT);
	if (!app->img.img_ptr)
		return (close_program(app), 0);
	app->img.addr = mlx_get_data_addr(app->img.img_ptr, &app->img.bpp,
			&app->img.line_len, &app->img.endian);
	if (!app->img.addr)
		return (close_program(app), 0);
	mlx_put_image_to_window(app->mlx, app->win, app->img.img_ptr, 0, 0);
	mlx_hook(app->win, 17, 0, close_program, app);
	mlx_hook(app->win, 2, 1L << 0, key_handler, app);
	mlx_loop(app->mlx);
}
