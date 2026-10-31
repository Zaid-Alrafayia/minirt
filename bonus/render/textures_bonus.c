/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 17:59:04 by jalghamd          #+#    #+#             */
/*   Updated: 2026/10/31 23:51:11 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

static int	load_single_texture(void *mlx, t_tex *tex, char *path)
{
	if (!path)
		return (1);
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img || tex->width <= 0 || tex->height <= 0)
	{
		ft_putstr_fd("Error\nFailed to load texture file\n", 2);
		return (0);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	return (1);
}

int	init_textures(t_app *app)
{
	t_list		*curr;
	t_object	*obj;

	curr = app->scene.objects;
	while (curr)
	{
		obj = (t_object *)curr->content;
		if (obj->tex_path)
		{
			if (!load_single_texture(app->mlx, &obj->tex, obj->tex_path))
				return (0);
		}
		if (obj->bump_path)
		{
			if (!load_single_texture(app->mlx, &obj->bump, obj->bump_path))
				return (0);
		}
		curr = curr->next;
	}
	return (1);
}

static t_color	get_pixel(t_tex *tex, int x, int y)
{
	unsigned char	*p;

	x = (x % tex->width + tex->width) % tex->width;
	y = (y % tex->height + tex->height) % tex->height;
	p = (unsigned char *)(tex->addr
			+ (y * tex->line_len + x * (tex->bpp / 8)));
	return ((t_color){p[2] / 255.0, p[1] / 255.0, p[0] / 255.0});
}

t_color	get_texture_color(t_hit *hit, t_tex *tex)
{
	double	uv[4];
	t_color	c[4];
	t_color	t[2];

	get_object_uv(hit, &uv[0], &uv[1]);
	if (hit->obj->type == OBJ_PLANE)
	{
		uv[0] = (uv[0] * 0.05 * tex->height / tex->width) + 0.5;
		uv[1] = (uv[1] * 0.05) + 0.5;
	}
	uv[0] = (uv[0] - floor(uv[0])) * tex->width;
	uv[1] = (1.0 - (uv[1] - floor(uv[1]))) * tex->height;
	uv[2] = uv[0] - floor(uv[0]);
	uv[3] = uv[1] - floor(uv[1]);
	c[0] = get_pixel(tex, (int)uv[0], (int)uv[1]);
	c[1] = get_pixel(tex, (int)uv[0] + 1, (int)uv[1]);
	c[2] = get_pixel(tex, (int)uv[0], (int)uv[1] + 1);
	c[3] = get_pixel(tex, (int)uv[0] + 1, (int)uv[1] + 1);
	t[0] = (t_color){c[0].r * (1 - uv[2]) + c[1].r * uv[2], c[0].g
		* (1 - uv[2]) + c[1].g * uv[2], c[0].b * (1 - uv[2]) + c[1].b * uv[2]};
	t[1] = (t_color){c[2].r * (1 - uv[2]) + c[3].r * uv[2], c[2].g
		* (1 - uv[2]) + c[3].g * uv[2], c[2].b * (1 - uv[2]) + c[3].b * uv[2]};
	return ((t_color){t[0].r * (1 - uv[3]) + t[1].r * uv[3], t[0].g
		* (1 - uv[3]) + t[1].g * uv[3], t[0].b * (1 - uv[3]) + t[1].b * uv[3]});
}

void	destroy_textures(t_app *app)
{
	t_list		*curr;
	t_object	*obj;

	curr = app->scene.objects;
	while (curr)
	{
		obj = (t_object *)curr->content;
		if (obj->tex.img)
		{
			mlx_destroy_image(app->mlx, obj->tex.img);
			obj->tex.img = NULL;
		}
		if (obj->bump.img)
		{
			mlx_destroy_image(app->mlx, obj->bump.img);
			obj->bump.img = NULL;
		}
		curr = curr->next;
	}
}
