/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 15:11:59 by jalghamd          #+#    #+#             */
/*   Updated: 2026/10/04 00:56:15 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

static void	rm_whitespaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t' || line[i] == '\r' || line[i] == '\v'
			|| line[i] == '\f')
			line[i] = ' ';
		i++;
	}
}

void	free_split(char **parts)
{
	int	i;

	if (!parts)
		return ;
	i = 0;
	while (parts[i])
	{
		free(parts[i]);
		i++;
	}
	free(parts);
}

static int	dispatch_id(char **parts, t_app *app)
{
	int	status;

	status = 0;
	if (ft_strncmp(parts[0], "A", 2) == 0)
		status = init_ambient(parts, app);
	else if (ft_strncmp(parts[0], "C", 2) == 0)
		status = init_camera(parts, app);
	else if (ft_strncmp(parts[0], "L", 2) == 0)
		status = init_light(parts, app);
	else if (ft_strncmp(parts[0], "sp", 3) == 0)
		status = init_sphere(parts, app);
	else if (ft_strncmp(parts[0], "pl", 3) == 0)
		status = init_plane(parts, app);
	else if (ft_strncmp(parts[0], "cy", 3) == 0)
		status = init_cylinder(parts, app);
	return (status);
}

static int	parse_line(char *line, t_app *app)
{
	char	**parts;
	int		status;

	rm_whitespaces(line);
	parts = ft_split(line, ' ');
	if (!parts || !parts[0])
	{
		free_split(parts);
		return (1);
	}
	status = dispatch_id(parts, app);
	if (!status)
		ft_putstr_fd("Error\nunknown ID or invalid value in scene file\n", 2);
	else if (status == -1)
		ft_putstr_fd("Error\nonly one ambient light is allowed\n", 2);
	else if (status == -2)
		ft_putstr_fd("Error\nonly one camera is allowed\n", 2);
	else if (status == -3)
		ft_putstr_fd("Error\ncomponant data incorrect\n", 2);
	free_split(parts);
	return (status);
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

int	read_fscene(char *file, t_app *app)
{
	int		fd;
	char	*line;
	int		len;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (parse_line(line, app) <= 0)
		{
			free(line);
			clean_gnl(fd);
			close(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!check_lca(fd, app, line))
		return (0);
	close(fd);
	return (1);
}
