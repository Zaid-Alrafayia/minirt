/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 15:11:59 by jalghamd          #+#    #+#             */
/*   Updated: 2026/09/29 22:12:24 by jalghamd         ###   ########.fr       */
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
	free_split(parts);
	return (status);
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
		if (!parse_line(line, app))
		{
			free(line);
			clean_gnl(fd);
			close(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
