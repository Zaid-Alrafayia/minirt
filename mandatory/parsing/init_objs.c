/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 16:14:34 by jalghamd          #+#    #+#             */
/*   Updated: 2026/09/29 19:48:29 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

int	init_sphere(char **parts, t_app *app)
{
	t_object	*obj;
	t_sphere	*sp;
	t_color		color;

	color = parse_color(parts[3]);
	if (!is_valid_color(color))
		return (0);
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (0);
	sp = malloc(sizeof(t_sphere));
	if (!sp)
	{
		free(obj);
		return (0);
	}
	sp->center = parse_vec3(parts[1]);
	sp->diameter = ft_atof(parts[2]);
	obj->type = OBJ_SPHERE;
	obj->color = color;
	obj->data = sp;
	ft_lstadd_back(&app->scene.objects, ft_lstnew(obj));
	return (1);
}

int	init_plane(char **parts, t_app *app)
{
	t_object	*obj;
	t_plane		*pl;
	t_color		color;

	color = parse_color(parts[3]);
	if (!is_valid_color(color))
		return (0);
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (0);
	pl = malloc(sizeof(t_plane));
	if (!pl)
	{
		free(obj);
		return (0);
	}
	pl->point = parse_vec3(parts[1]);
	pl->normal = parse_vec3(parts[2]); //zaid: pl->normal = call ur func here instead (replace the assignment)
	obj->type = OBJ_PLANE;
	obj->color = color;
	obj->data = pl;
	ft_lstadd_back(&app->scene.objects, ft_lstnew(obj));
	return (1);
}

int	init_cylinder(char **parts, t_app *app)
{
	t_object	*obj;
	t_cylinder	*cy;
	t_color		color;

	color = parse_color(parts[5]);
	if (!is_valid_color(color))
		return (0);
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (0);
	cy = malloc(sizeof(t_cylinder));
	if (!cy)
	{
		free(obj);
		return (0);
	}
	cy->center = parse_vec3(parts[1]);
	cy->axis = parse_vec3(parts[2]); //zaid: cy->axis = call ur func here instead (replace the assignment)
	cy->diameter = ft_atof(parts[3]);
	cy->height = ft_atof(parts[4]);
	obj->type = OBJ_CYLINDER;
	obj->color = color;
	obj->data = cy;
	ft_lstadd_back(&app->scene.objects, ft_lstnew(obj));
	return (1);
}
