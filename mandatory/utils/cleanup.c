/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:46:30 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/09/29 22:15:46 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

void	free_object(void *content)
{
	t_object	*obj;

	obj = (t_object *)content;
	if (!obj)
		return ;
	if (obj->data)
		free(obj->data);
	free(obj);
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->objects)
		ft_lstclear(&scene->objects, free_object);
	if (scene->lights)
		ft_lstclear(&scene->lights, free);
}

void	clean_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

int	check_lca(int fd, t_app *app, char *line)
{
	if (app->scene.lights_count < 1)
		ft_putstr_fd("Error\nat least one light is needed\n", 2);
	else if (!app->scene.has_amb)
		ft_putstr_fd("Error\none ambient light is needed\n", 2);
	else if (!app->scene.has_cam)
		ft_putstr_fd("Error\none camera is needed\n", 2);
	else
		return (1);
	free(line);
	clean_gnl(fd);
	close(fd);
	return (0);
}
