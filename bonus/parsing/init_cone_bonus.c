/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cone_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 07:17:02 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/10/25 07:23:17 by zaalrafa         ###   ########.fr       */
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
	if (arrstr_len(parts) == 5 || arrstr_len(parts) == 6)
		(*co)->texture_map = ft_strdup(parts[4]);
	if (arrstr_len(parts) == 6)
		(*co)->bump_map = ft_strdup(parts[5]);
	if ((*co)->diameter <= 0 || (*co)->height <= 0)
	{
		free(*co);
		return (0);
	}
	(*co)->k_sq = (((*co)->diameter / 2) * ((*co)->diameter / 2))
		/ ((*co)->height * (*co)->height);
	return (1);
}

static int	add_cone(t_cone *co, t_color color, t_app *app)
{
	t_object	*obj;
	t_list		*node;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (free(co), 0);
	obj->type = OBJ_CONE;
	obj->color = color;
	obj->data = co;
	node = ft_lstnew(obj);
	if (!node)
		return (free_object(obj), 0);
	ft_lstadd_back(&app->scene.objects, node);
	return (1);
}

int	init_cone(char **parts, t_app *app)
{
	t_cone *co;
	t_color color;

	if (!(arrstr_len(parts) >= 6 && arrstr_len(parts) <= 8))
		return (-3);
	color = parse_color(parts[5]);
	if (!is_valid_color(color) || !is_num(parts[3]) || !is_num(parts[4]))
		return (0);
	if (!init_cone_data(parts, &co))
		return (0);
	return (add_cone(co, color, app));
}