/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cone_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 07:17:02 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/10/28 01:01:55 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

static int	init_cone_data(char **parts, t_cone **co)
{
	*co = malloc(sizeof(t_cone));
	if (!*co)
		return (0);
	if (parse_vec3(parts[1], &(*co)->center) || parse_vec3(parts[2],
			&(*co)->axis) || !is_valid_normal((*co)->axis))
	{
		free(*co);
		return (0);
	}
	(*co)->diameter = ft_atof(parts[3]);
	(*co)->height = ft_atof(parts[4]);
	(*co)->axis = normvec((*co)->axis);
	if ((*co)->diameter <= 0 || (*co)->height <= 0)
	{
		free(*co);
		return (0);
	}
	(*co)->k_sq = (((*co)->diameter / 2) * ((*co)->diameter / 2))
		/ ((*co)->height * (*co)->height);
	return (1);
}

static int	add_cone(t_cone *co, t_color color, char **parts, t_app *app)
{
	t_object	*obj;
	t_list		*node;

	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		free(co);
		return (0);
	}
	obj->type = OBJ_CONE;
	obj->color = color;
	obj->data = co;
	set_textures(obj, parts, 6);
	node = ft_lstnew(obj);
	if (!node)
	{
		free_object(obj);
		return (0);
	}
	ft_lstadd_back(&app->scene.objects, node);
	return (1);
}

int	init_cone(char **parts, t_app *app)
{
	t_cone	*co;
	t_color	color;

	if (!(arrstr_len(parts) >= 6 && arrstr_len(parts) <= 8))
		return (-3);
	color = parse_color(parts[5]);
	if (!is_valid_color(color) || !is_num(parts[3]) || !is_num(parts[4]))
		return (0);
	if (!init_cone_data(parts, &co))
		return (0);
	return (add_cone(co, color, parts, app));
}
