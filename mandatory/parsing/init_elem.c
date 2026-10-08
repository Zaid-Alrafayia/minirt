/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_elem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 16:12:19 by jalghamd          #+#    #+#             */
/*   Updated: 2026/10/07 11:37:04 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

int	init_ambient(char **parts, t_app *app)
{
	if (arrstr_len(parts) != 3)
		return (-3);
	if (app->scene.has_amb)
		return (-1);
	if (!is_num(parts[1]))
		return (0);
	app->scene.amb_light.ratio = ft_atof(parts[1]);
	if (app->scene.amb_light.ratio < 0.0 || app->scene.amb_light.ratio > 1.0)
		return (0);
	app->scene.amb_light.color = parse_color(parts[2]);
	if (!is_valid_color(app->scene.amb_light.color))
		return (0);
	app->scene.has_amb = true;
	return (1);
}

int	init_camera(char **parts, t_app *app)
{
	if (app->scene.has_cam)
		return (-2);
	if (arrstr_len(parts) != 4 || parse_vec3(parts[1], &app->scene.cam.pos)
		|| parse_vec3(parts[2], &app->scene.cam.dir)
		|| is_zero_vec(app->scene.cam.dir))
		return (-3);
	app->scene.cam.dir = normvec(app->scene.cam.dir);
	if (!is_num(parts[3]))
		return (0);
	app->scene.cam.fov = ft_atof(parts[3]);
	if (app->scene.cam.fov < 0.0 || app->scene.cam.fov > 180.0)
		return (0);
	app->scene.has_cam = true;
	return (1);
}

static int	init_light_data(char **parts, t_light **light)
{
	*light = malloc(sizeof(t_light));
	if (!*light)
		return (0);
	if (parse_vec3(parts[1], &(*light)->pos))
	{
		free(*light);
		return (-3);
	}
	(*light)->brightness = ft_atof(parts[2]);
	(*light)->color = parse_color(parts[3]);
	return (1);
}

static int	add_light(t_light *light, t_app *app)
{
	t_list	*node;

	node = ft_lstnew(light);
	if (!node)
	{
		free(light);
		return (0);
	}
	ft_lstadd_back(&app->scene.lights, node);
	app->scene.lights_count++;
	return (1);
}

int	init_light(char **parts, t_app *app)
{
	t_light	*light;
	double	brightness;
	t_color	color;
	int		status;

	if (arrstr_len(parts) != 4)
		return (-3);
	brightness = ft_atof(parts[2]);
	color = parse_color(parts[3]);
	if (!is_valid_color(color) || brightness < 0.0 || brightness > 1.0
		|| !is_num(parts[2]))
		return (0);
	status = init_light_data(parts, &light);
	if (status != 1)
		return (status);
	return (add_light(light, app));
}
